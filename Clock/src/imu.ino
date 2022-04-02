//                             ___          ___                 ___          ___         ___     //
//                            /\__\        /\  \               /\__\        /\__\      /|  |     //
//                 ___       /:/ _/_       \:\  \       ___   /:/ _/_      /:/ _/_    |:|  |     //
//                /\__\     /:/ /\  \       \:\  \     /\__\ /:/ /\  \    /:/ /\__\   |:|  |     //
//  ___     ___  /:/__/    /:/ /::\  \  ___ /::\  \   /:/  //:/ /::\  \  /:/ /:/  / __|:|__|     //
// /\  \   /\__\/::\  \   /:/__\/\:\__\/\  /:/\:\__\ /:/__//:/_/:/\:\__\/:/_/:/  / /::::\__\_____//
// \:\  \ /:/  /\/\:\  \__\:\  \ /:/  /\:\/:/  \/__//::\  \\:\/:/ /:/  /\:\/:/  /  ~~~~\::::/___///
//  \:\  /:/  /  ~~\:\/\__\\:\  /:/  /  \::/__/    /:/\:\  \\::/ /:/  /  \::/__/       |:|~~|    //
//   \:\/:/  /      \::/  / \:\/:/  /    \:\  \    \/__\:\  \\/_/:/  /    \:\  \       |:|  |    //
//    \::/  /       /:/  /   \::/  /      \:\__\        \:\__\ /:/  /      \:\__\      |:|__|    //
//     \/__/        \/__/     \/__/        \/__/         \/__/ \/__/        \/__/      |/__/     //4

#include <Arduino.h>
#include <Wire.h>
#include "imu.h"
#include "pixel.h"
#include "timeclock.h"
#include "buzzer.h"

//Initializing I2C form IMU
void IMUI2CInit()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

//Reading from IMU
void readIMU()
{
  Wire.beginTransmission(MPU_addr); //Starting I2C connection
  Wire.write(0x3B);                 //Starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);      //Hold I2C connection

  Wire.requestFrom(MPU_addr, 14, true); // Request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

//Controlling leds with IMU
void imuRGB()
{
  readIMU();
  if (mode == PIXEL_IMU)
  {
    if (AcX > 2500 && AcY < -1500)
    {
      green = green + 1;
    }
    else if (AcX > 3000)
    {
      red = red + 1;
    }
    else if (AcY < -3000)
    {
      blue = blue + 1;
    }

    if (AcX < -2500 && AcY > 1500)
    {
      green = green - 1;
    }
    else if (AcX < -3000)
    {
      red = red - 1;
    }
    else if (AcY > 3000)
    {
      blue = blue - 1;
    }

    if (red > MAX_COLOR)
    {
      red = MAX_COLOR;
    }
    else if (red < 0)
    {
      red = 0;
    }

    if (blue > MAX_COLOR)
    {
      blue = MAX_COLOR;
    }
    else if (blue < 0)
    {
      blue = 0;
    }

    if (green > MAX_COLOR)
    {
      green = MAX_COLOR;
    }
    else if (green < 0)
    {
      green = 0;
    }

    pixelSetFullRGB(red, green, blue);
  }
}

void imuStopAlarm()
{
  readIMU();
  if (AcX >= 32500 || AcY >= 32500 || AcX <= -32500 || AcY <= -32500)
  {
    stopAlarm = 1;
    ledcWriteTone(LEDC_CHANNEL_0, 0);
  }
}

void imuColorSet()
{
  timeWait = millis() - timeWaitTot;
  readIMU();
  if (GyZ <= -15000 && timeWait >= 250)
  {
    mode++;
    timeWaitTot = millis();
    if (mode == 4)
    {
      mode = 0;
    }
  }
  else if (GyZ >= 15000 && timeWait >= 250)
  {
    mode--;
    timeWaitTot = millis();
    if (mode == -1)
    {
      mode = 3;
    }
  }
}