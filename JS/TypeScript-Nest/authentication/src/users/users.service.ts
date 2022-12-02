import { Injectable } from '@nestjs/common';
import { InjectModel } from '@nestjs/sequelize';
import { UserEntity } from 'src/entities/user.entity';
import { Repository } from 'typeorm';
import { CreateUserDto } from './dto/create-user.dto';

@Injectable()
export class UsersService {
    constructor(@InjectModel(UserEntity) private usersRepository: Repository<UserEntity>) { }

    async createUser(dto: CreateUserDto): Promise<UserEntity> {
        let user = await this.usersRepository.save(dto);
        return user
    }

    async getAllUsers(): Promise<UserEntity[]> {
        return await this.usersRepository.find({
            select: {
                id: true,
                name: true,
                email: true
            }
        }
        );
    }

    async getUserByEmail(email: string): Promise<UserEntity> {
        return this.usersRepository.findOneBy({ email });
    }
}
