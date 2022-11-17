
import { Entity, Column, PrimaryGeneratedColumn, CreateDateColumn, UpdateDateColumn } from 'typeorm';

@Entity('users')
export class UserEntity {
  @PrimaryGeneratedColumn('uuid')
  id: number;

  @Column({nullable:true})
  name: string;

  @Column({unique:true})
  email: string;

  @Column({nullable:false})
  password: string

  @CreateDateColumn()
  createdAt:Date

  @UpdateDateColumn()
  updateAt:Date
}
