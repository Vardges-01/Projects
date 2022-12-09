import { ApiProperty } from '@nestjs/swagger';
import { IsEmail, IsString } from 'class-validator';

export class CreateUserDto {
  @ApiProperty({
    type: String,
    description: 'User Name',
  })
  @IsString()
  name: string;

  @ApiProperty({
    type: String,
    description: 'User Email',
  })
  @IsString()
  @IsEmail()
  email: string;

  @ApiProperty({
    type: String,
    description: 'User Password',
  })
  @IsString()
  password: string;
}