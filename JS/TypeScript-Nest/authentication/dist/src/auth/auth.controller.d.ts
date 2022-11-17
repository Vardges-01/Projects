import { CreateUserDto } from 'src/users/dto/create-user.dto';
import { AuthService } from './auth.service';
export declare class AuthController {
    private authService;
    constructor(authService: AuthService);
    login(userDto: CreateUserDto): Promise<{
        accessToken: string;
    }>;
    regostration(userDto: CreateUserDto): Promise<{
        accessToken: string;
    }>;
}
