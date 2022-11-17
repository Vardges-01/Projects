import { CreateUserDto } from './dto/create-user.dto';
import { UsersService } from './users.service';
export declare class UsersController {
    private usersService;
    constructor(usersService: UsersService);
    create(userDto: CreateUserDto): Promise<import("../entities/user.entity").UserEntity>;
    getAll(): Promise<import("../entities/user.entity").UserEntity[]>;
}
