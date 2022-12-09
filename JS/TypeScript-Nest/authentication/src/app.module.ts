import { Module } from "@nestjs/common";
import { ConfigModule } from "@nestjs/config";
import { TypeOrmModule } from '@nestjs/typeorm';
import { UserEntity } from "./entities/user.entity";

import { AuthModule } from './auth/auth.module';
import { APP_GUARD } from "@nestjs/core";
import { AtGuard } from "./common/guards";


@Module({
    controllers:[],
    providers: [
        {
          provide: APP_GUARD,
          useClass: AtGuard,
        },
      ],
    imports: [
        ConfigModule.forRoot({
            envFilePath: `config/.${process.env.NODE_ENV}.env`
        }),
        TypeOrmModule.forRoot({
            type: 'postgres',
            host: process.env.POSTGRES_HOST,
            port: Number(process.env.POSTGRES_PORT),
            username: process.env.POSTGRES_USER,
            password: process.env.POSTGRES_PASSWORD,
            database: process.env.POSTGRES_DB,
            entities: [UserEntity], // TODO Postgres Connect
            autoLoadEntities: true,
            synchronize: true
        }),
        AuthModule
    ]

})
export class AppModule {

}