import { Body, Controller, HttpCode, HttpStatus, Post, Req, UseGuards } from '@nestjs/common';
import { AuthService } from './auth.service';
import { CreateUserDto } from './dto/create-user.dto';
import { LoginUserDto } from './dto/login-user.dto';
import { Tokens } from './types';
import { Request } from 'express';
import { AtGuard, RtGuard } from 'src/common/guards';
import { GetCurrentUser, GetCurrentUserId, Public } from 'src/common/decorators';

@Controller('auth')
export class AuthController {
    constructor(private authService: AuthService) { }

    @Public()
    @Post("signup")
    @HttpCode(HttpStatus.CREATED)
    signup(@Body() dto: CreateUserDto): Promise<Tokens> {
        return this.authService.signup(dto);
    }


    @Public()
    @Post("signin")
    @HttpCode(HttpStatus.OK)
    signin(@Body() dto: LoginUserDto): Promise<Tokens> {
        return this.authService.signin(dto);
    }


    @Post("logout")
    @HttpCode(HttpStatus.OK)
    logout(@GetCurrentUserId() userId: number) {
        return this.authService.logout(userId);
    }

    @Public()
    @UseGuards(RtGuard)
    @Post("refresh")
    @HttpCode(HttpStatus.OK)
    refreshTokens(
        @GetCurrentUserId() userId: number,
        @GetCurrentUser("refreshToken") refreshToken: string
    ) {
        
        return this.authService.refreshTokens(userId, refreshToken);
    }
}
