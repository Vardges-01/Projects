import { HttpException, HttpStatus, Injectable, UnauthorizedException } from '@nestjs/common';
import { CreateUserDto } from 'src/users/dto/create-user.dto';
import { UsersService } from 'src/users/users.service';
import {JwtService} from '@nestjs/jwt';
import * as bcrypt from 'bcryptjs'
import { UserEntity } from 'src/entities/user.entity';
import { LoginUserDto } from 'src/users/dto/login-user.dto';

@Injectable()
export class AuthService {

    constructor( private userService: UsersService,
                 private jwtService: JwtService) { }

    async login(userDto: LoginUserDto){
        let user = await this.validateUser(userDto);
        return this.generateToken(user);
    }

    async regostration(userDto: CreateUserDto) {
        const userData = await this.userService.getUserByEmail(userDto.email);

        if(userData){
            throw new HttpException("User already exist", HttpStatus.BAD_REQUEST)
        }

        const hashPassword = await bcrypt.hash(userDto.password, 6);
        const user = await this.userService.createUser({...userDto, password: hashPassword})
        return this.generateToken(user);
    }

    async generateToken(user: UserEntity){
        let payload = { id: user.id, name: user.name, email: user.email };
        return {
            accessToken: this.jwtService.sign(payload)
        }
    }

    private async validateUser(userDto: LoginUserDto) {
        const userData = await this.userService.getUserByEmail(userDto.email);
        const passwordEquals = await bcrypt.compare(userDto.password, userData.password);

        if(userData && passwordEquals){
            return userData;
        }

        throw new UnauthorizedException({ message: "Wrong Password" })

    }


}
