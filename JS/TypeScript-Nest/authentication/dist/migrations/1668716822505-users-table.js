"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.usersTable1668716822505 = void 0;
class usersTable1668716822505 {
    async up(queryRunner) {
        await queryRunner.query(`CREATE TABLE IF NOT EXISTS "users" ("id" uuid NOT NULL DEFAULT uuid_generate_v4(), "name" text NOT NULL, "email" text NOT NULL, "password" text NOT NULL, UNIQUE ("email"),created_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
            updated_at TIMESTAMPTZ NOT NULL DEFAULT NOW(), PRIMARY KEY ("id"))`);
    }
    async down(queryRunner) {
    }
}
exports.usersTable1668716822505 = usersTable1668716822505;
//# sourceMappingURL=1668716822505-users-table.js.map