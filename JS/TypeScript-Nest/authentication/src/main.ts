import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';

async function start() {
  console.log(process.env);
 const PORT = process.env.PORT || 3000;
 const app =  await NestFactory.create(AppModule);

  await app.listen(PORT, () => console.log(`Server started: Port => ${PORT}`));
}

start();
