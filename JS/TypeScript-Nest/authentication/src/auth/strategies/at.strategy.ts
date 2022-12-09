import { Injectable } from "@nestjs/common";
import {PassportStrategy} from "@nestjs/passport";
import {ExtractJwt,Strategy} from 'passport-jwt';

type JwtPayload = {
    id:string;
    email:string;
}

@Injectable()
export class AtStrategy extends PassportStrategy(Strategy,"jwt"){
    constructor(){
        super({
            jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
            secretOrKey: 'AT_SECRET'
        })
    }

    validate(payload: JwtPayload){
        return payload;
    }
}