import { ForbiddenException, HttpException, HttpStatus, Injectable, UnauthorizedException } from '@nestjs/common';
import { CreateUserDto } from './dto/create-user.dto';
import * as bcrypt from 'bcryptjs'
import * as argon from 'argon2';
import { UserEntity } from 'src/entities/user.entity';
import { LoginUserDto } from './dto/login-user.dto';
import { InjectModel } from '@nestjs/sequelize';
import { Repository } from 'typeorm';
import { Tokens } from './types';
import { JwtService } from '@nestjs/jwt';

@Injectable()
export class AuthService {

    constructor(@InjectModel(UserEntity) private usersRepository: Repository<UserEntity>,
        private jwtService: JwtService) { }

    async signup(dto: CreateUserDto): Promise<Tokens> {
        const hashPassword = await this.hashData(dto.password);
        const newUser = await this.usersRepository.save({
            name: dto.name,
            email: dto.email,
            password: hashPassword
        })

        const tokens = await this.getTokens(newUser.id, newUser.email);
        await this.updateRtHash(newUser.id, tokens.refresh_token)

        return tokens;
    }

    async signin(dto: LoginUserDto): Promise<Tokens> {

        const user = await this.usersRepository.findOneBy({ email: dto.email });
        
        if (!user) throw new ForbiddenException("Access Denied");

        const passwordMatches = await argon.verify(user.password, dto.password);

        if(!passwordMatches) throw new UnauthorizedException({ message: "Wrong Password" })
        
        const tokens = await this.getTokens(user.id, user.email);
        await this.updateRtHash(user.id, tokens.refresh_token)

        return tokens;
    }

    async logout(userId: number) {
        await this.usersRepository.save({
            id: userId,
            hashRt: null
        })
     }


    async refreshTokens(userId:number, rt:string) {
        const user = await this.usersRepository.findOneBy({ id: userId });

        if(!user || (user && !user.hashRt)) throw new ForbiddenException("Access Denied");
        
        const rtMatches = await argon.verify(user.hashRt, rt);
        if(!rtMatches) throw new ForbiddenException("Access Denied");

        const tokens = await this.getTokens(user.id, user.email);
        await this.updateRtHash(user.id, tokens.refresh_token)

        return tokens;
     }

    async updateRtHash(userId: number, rt: string) {
        const hash = await this.hashData(rt);
        await this.usersRepository.save({
            id: userId,
            hashRt: hash
        })
    }
    
    async getTokens(userId: number, email: string) {
        const [at, rt] = await Promise.all([
            this.jwtService.signAsync({
                id: userId,
                email
            },
                {
                    secret: "AT_SECRET",
                    expiresIn: 60 * 15
                }
            ),

            this.jwtService.signAsync({
                id: userId,
                email
            },
                {
                    secret: "RT_SECRET",
                    expiresIn: 60 * 60 * 24 * 7
                })
        ]);

        return {
            access_token:at,
            refresh_token:rt,
        }
    }


    hashData(data: string) {
        return argon.hash(data)
    }

}
