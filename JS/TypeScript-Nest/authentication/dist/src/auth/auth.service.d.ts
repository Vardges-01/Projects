import { CreateUserDto } from 'src/users/dto/create-user.dto';
import { UsersService } from 'src/users/users.service';
import { JwtService } from '@nestjs/jwt';
import { UserEntity } from 'src/entities/user.entity';
import { LoginUserDto } from 'src/users/dto/login-user.dto';
export declare class AuthService {
    private userService;
    private jwtService;
    constructor(userService: UsersService, jwtService: JwtService);
    login(userDto: LoginUserDto): Promise<{
        accessToken: string;
    }>;
    regostration(userDto: CreateUserDto): Promise<{
        accessToken: string;
    }>;
    generateToken(user: UserEntity): Promise<{
        accessToken: string;
    }>;
    private validateUser;
}
