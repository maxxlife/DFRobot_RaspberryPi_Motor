#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <thread>
#include <chrono>

int main(int argc, char **argv)
{
  // Setup I2C communication
  int fd = wiringPiI2CSetup(0x10);
  int frequency = 1000;
  int reg;
  int count = 0;
  int speed_left;
  int speed_right;

  if (fd == -1)
  {
    std::cout << "Failed to init I2C communication.\n";
    return -1;
  }
  std::cout << "I2C communication successfully setup.\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  frequency = int(frequency / 50);

  // set control mode
  reg = 0x3;
  wiringPiI2CWriteReg8(fd, reg, 0);

  // Stop motors
  reg = 0xf;
  wiringPiI2CWriteReg8(fd, reg, 5);
  reg = 0x12;
  wiringPiI2CWriteReg8(fd, reg, 5);

  // Disable encoder
  reg = 0x4;
  wiringPiI2CWriteReg8(fd, reg, 0);
  reg = 0x9;
  wiringPiI2CWriteReg8(fd, reg, 0);

  // Setup frequency
  reg = 0xe;
  wiringPiI2CWriteReg8(fd, reg, frequency);

  // Going forward
  while (count < 5)
  {
    // forward left
    reg = 0xf;
    wiringPiI2CWriteReg8(fd, reg, 2);
    reg = 0x10;
    speed_left = 20;
    wiringPiI2CWriteReg8(fd, reg, speed_left);

    // forward right
    reg = 0x12;
    wiringPiI2CWriteReg8(fd, reg, 1);
    reg = 0x13;
    speed_right = 10;
    wiringPiI2CWriteReg8(fd, reg, speed_right);

    count++;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  count = 0;

  // Going backward
  while (count < 5)
  {
    // backward left
    reg = 0xf;
    wiringPiI2CWriteReg8(fd, reg, 1);
    reg = 0x10;
    speed_left = 20;
    wiringPiI2CWriteReg8(fd, reg, speed_left);

    // backward right
    reg = 0x12;
    wiringPiI2CWriteReg8(fd, reg, 2);
    reg = 0x13;
    speed_right = 10;
    wiringPiI2CWriteReg8(fd, reg, speed_right);

    count++;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  // stop all
  reg = 0xf;
  wiringPiI2CWriteReg8(fd, reg, 5);
  reg = 0x12;
  wiringPiI2CWriteReg8(fd, reg, 5);
}