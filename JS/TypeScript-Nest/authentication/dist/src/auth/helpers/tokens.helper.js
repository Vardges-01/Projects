"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const common_1 = require("@nestjs/common");
const argon = require("argon2");
async function refreshTokens(userId, rt) {
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
async function updateRtHash(userId, rt) {
    const hash = await this.hashData(rt);
    await this.usersRepository.save({
        id: userId,
        hashRt: hash
    });
}
async function getTokens(userId, email) {
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
//# sourceMappingURL=tokens.helper.js.map