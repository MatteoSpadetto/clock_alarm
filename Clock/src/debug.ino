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
//     \/__/        \/__/     \/__/        \/__/         \/__/ \/__/        \/__/      |/__/     //

#include <Arduino.h>
#include "debug.h"
#include "imu.h"
#include "pixel.h"
#include "timeclock.h"
#include "buttons.h"

//Counter debug of the loop where is called
void loopCountDebug()
{
    currentLoopMillis = millis();
    timeLoop = currentLoopMillis - previousLoopMillis;
    previousLoopMillis = currentLoopMillis;
    Serial.println("counterLoop:");
    Serial.println(counterLoop);
    Serial.println("timeLoop:");
    Serial.println(timeLoop);
    counterLoop++;
}

//IMU datas debug
void imuDebug()
{
    Serial.print("AcX = ");
    Serial.print(AcX);
    Serial.print(" | AcY = ");
    Serial.print(AcY);
    Serial.print(" | AcZ = ");
    Serial.print(AcZ);
    Serial.print(" | Tmp = ");
    Serial.print(Tmp / 340.00 + 36.53); //Equation for temperature in degrees C from datasheet
    Serial.print(" | GyX = ");
    Serial.print(GyX);
    Serial.print(" | GyY = ");
    Serial.print(GyY);
    Serial.print(" | GyZ = ");
    Serial.println(GyZ);
}

//IMU RGB datas debug after conversion
void imuRGBDebug()
{
    Serial.print("RED = ");
    Serial.print(red);
    Serial.print(" | ");

    Serial.print("GREEN = ");
    Serial.print(green);
    Serial.print(" | ");

    Serial.print("BLUE = ");
    Serial.println(blue);
}

//Local date and time debug
void timeDebug()
{
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    Serial.print("HOURS = ");
    Serial.print(hours);
    Serial.print(" | ");

    Serial.print("MINUTES = ");
    Serial.print(minutes);
    Serial.print(" | ");

    Serial.print("SECONDS = ");
    Serial.println(seconds);
}

//Buttons debug
void buttonsDebug()
{
    Serial.print("BTN_PLUS = ");
    Serial.print(digitalRead(buttonPlus.PIN));
    Serial.print(" | BTN_MINUS = ");
    Serial.print(digitalRead(buttonMinus.PIN));
    Serial.print(" | BTN_OK = ");
    Serial.println(digitalRead(buttonOk.PIN));
}

void timeAlarmDebug()
{
    Serial.print("timeMillis = ");
    Serial.print(timeMillis);
    Serial.print(" | alarmTime = ");
    Serial.print(alarmTime);
    Serial.print(" | stopAlarm = ");
    Serial.println(stopAlarm);
}