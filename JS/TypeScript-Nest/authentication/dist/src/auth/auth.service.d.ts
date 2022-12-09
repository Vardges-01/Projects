import { CreateUserDto } from './dto/create-user.dto';
import { UserEntity } from 'src/entities/user.entity';
import { LoginUserDto } from './dto/login-user.dto';
import { Repository } from 'typeorm';
import { Tokens } from './types';
import { JwtService } from '@nestjs/jwt';
export declare class AuthService {
    private usersRepository;
    private jwtService;
    constructor(usersRepository: Repository<UserEntity>, jwtService: JwtService);
    signup(dto: CreateUserDto): Promise<Tokens>;
    signin(dto: LoginUserDto): Promise<Tokens>;
    logout(userId: number): Promise<void>;
    refreshTokens(userId: number, rt: string): Promise<{
        access_token: string;
        refresh_token: string;
    }>;
    updateRtHash(userId: number, rt: string): Promise<void>;
    getTokens(userId: number, email: string): Promise<{
        access_token: string;
        refresh_token: string;
    }>;
    hashData(data: string): Promise<string>;
}
