"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
var __param = (this && this.__param) || function (paramIndex, decorator) {
    return function (target, key) { decorator(target, key, paramIndex); }
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.AuthService = void 0;
const common_1 = require("@nestjs/common");
const argon = require("argon2");
const user_entity_1 = require("../entities/user.entity");
const sequelize_1 = require("@nestjs/sequelize");
const typeorm_1 = require("typeorm");
const jwt_1 = require("@nestjs/jwt");
let AuthService = class AuthService {
    constructor(usersRepository, jwtService) {
        this.usersRepository = usersRepository;
        this.jwtService = jwtService;
    }
    async signup(dto) {
        try {
            const user = await this.usersRepository.findOneBy({ email: dto.email });
            if (user)
                throw new common_1.ConflictException("Email already exist");
            const hashPassword = await this.hashData(dto.password);
            const newUser = await this.usersRepository.save({
                name: dto.name,
                email: dto.email,
                password: hashPassword
            });
            const tokens = await this.getTokens(newUser.id, newUser.email);
            await this.updateRtHash(newUser.id, tokens.refresh_token);
            return tokens;
        }
        catch (error) {
            throw error;
        }
    }
    async signin(dto) {
        try {
            const user = await this.usersRepository.findOneBy({ email: dto.email });
            if (!user)
                throw new common_1.ForbiddenException("User Not Found");
            const passwordMatches = await argon.verify(user.password, dto.password);
            if (!passwordMatches)
                throw new common_1.UnauthorizedException({ message: "Wrong Password" });
            const tokens = await this.getTokens(user.id, user.email);
            await this.updateRtHash(user.id, tokens.refresh_token);
            return tokens;
        }
        catch (error) {
            throw error;
        }
    }
    async logout(userId) {
        await this.usersRepository.save({
            id: userId,
            hashRt: null
        });
    }
    async refreshTokens(userId, rt) {
        try {
            const user = await this.usersRepository.findOneBy({ id: userId });
            if (!user || (user && !user.hashRt))
                throw new common_1.ForbiddenException("Access Denied");
            const rtMatches = await argon.verify(user.hashRt, rt);
            if (!rtMatches)
                throw new common_1.ForbiddenException("Access Denied");
            const tokens = await this.getTokens(user.id, user.email);
            await this.updateRtHash(user.id, tokens.refresh_token);
            return tokens;
        }
        catch (error) {
            throw error;
        }
    }
    async updateRtHash(userId, rt) {
        const hash = await this.hashData(rt);
        await this.usersRepository.save({
            id: userId,
            hashRt: hash
        });
    }
    async getTokens(userId, email) {
        try {
            const [at, rt] = await Promise.all([
                this.jwtService.signAsync({
                    id: userId,
                    email
                }, {
                    secret: "AT_SECRET",
                    expiresIn: 60 * 15
                }),
                this.jwtService.signAsync({
                    id: userId,
                    email
                }, {
                    secret: "RT_SECRET",
                    expiresIn: 60 * 60 * 24 * 7
                })
            ]);
            return {
                access_token: at,
                refresh_token: rt,
            };
        }
        catch (error) {
            throw error;
        }
    }
    hashData(data) {
        return argon.hash(data);
    }
};
AuthService = __decorate([
    (0, common_1.Injectable)(),
    __param(0, (0, sequelize_1.InjectModel)(user_entity_1.UserEntity)),
    __metadata("design:paramtypes", [typeorm_1.Repository,
        jwt_1.JwtService])
], AuthService);
exports.AuthService = AuthService;
//# sourceMappingURL=auth.service.js.map