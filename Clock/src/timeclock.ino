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
#include "timeclock.h"
#include "buzzer.h"
#include "imu.h"

//Initialize date and time NTP server
void initTime()
{
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); //Init time from INRIM
}

//Storing local date and time
void storeLocalTime()
{
    if (millis() - prevMillis >= TIME_UPDATE || firstConn == 1)
    {
        if (!getLocalTime(&timeinfo)) //Collecting date and time
        {
            Serial.println("Failed to obtain time");
            return;
        }

        strftime(timeHoursBuff, sizeof(timeHoursBuff), "%H", &timeinfo);
        strftime(timeMinutesBuff, sizeof(timeMinutesBuff), "%M", &timeinfo);
        strftime(timeSecondsBuff, sizeof(timeSecondsBuff), "%S", &timeinfo);

        hours = atoi(timeHoursBuff);
        minutes = atoi(timeMinutesBuff);
        seconds = atoi(timeSecondsBuff);

        hoursMillis = hours * 60 * 60 * 1000;
        minutesMillis = minutes * 60 * 1000;
        secondsMillis = seconds * 1000;
        timeMillis = hoursMillis + minutesMillis + secondsMillis;
        prevMillis = millis();
        firstConn = 0;
    }
    else
    {
        tmpMillis = timeMillis + millis() - prevMillis;
        hours = floor(tmpMillis / 1000 / 60 / 60);
        tmpMillis = tmpMillis - (hours * 60 * 60 * 1000);
        minutes = floor(tmpMillis / 1000 / 60);
    }
}

void playAlarm()
{
    if (alarmHours == hours && alarmMinutes == minutes)
    {
        while (stopAlarm == 0)
        {
            playTone(0);
            imuStopAlarm();
        }
    }
}