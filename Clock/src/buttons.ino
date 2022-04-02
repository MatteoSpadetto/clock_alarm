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
#include "buttons.h"
#include "timeclock.h"
#include "timeseg.h"

//TODO: OVERFLOW IN TIME MIDNIGHT AFTER DAYS

void onButtonClick()
{
    timeDeboun = millis() - timeDebounTot;
    if (digitalRead(BTN_PLUS) == 0 && timeDeboun >= 175)
    {
        setAlarmPeriod = millis();
        setAlarm = 1;
        timeDebounTot = millis();
        alarmTime += (1000 * 60);
        if (alarmTime >= 0)
        {
            if (alarmTime == 86400000)
            {
                alarmTime = 0; //Deleting overflow possibilities
            }
            alarmHours = floor(alarmTime / 1000 / 60 / 60);
            int tmpAlarmTime = alarmTime - (alarmHours * 60 * 60 * 1000);
            alarmMinutes = floor(tmpAlarmTime / 1000 / 60);
            if (alarmMinutes == 60)
            {
                alarmMinutes = 0;
            }
            displaySeg(alarmHours, alarmMinutes, ALARM);
        }
        else
        {
            alarmHours = floor(alarmTime / 1000 / 60 / 60);
            int tmpAlarmTime = alarmTime - (alarmHours * 60 * 60 * 1000);
            alarmMinutes = floor(tmpAlarmTime / 1000 / 60);
            Serial.println("ciao1");
            Serial.println(alarmMinutes);
            if (alarmMinutes == 0)
            {
                alarmMinutes = 60;
                /*if (alarmHours == 0)
                {
                    alarmHours = 23;
                }*/
                alarmHours++;
            }
            displaySeg(23 - abs(alarmHours), 60 - abs(alarmMinutes), ALARM);
            alarmHours = 23 - abs(alarmHours);
            alarmMinutes = 60 - abs(alarmMinutes);
        }
        stopAlarm = 1;
    }
    else if (digitalRead(BTN_MINUS) == 0 && timeDeboun >= 175)
    {
        setAlarmPeriod = millis();
        setAlarm = 1;
        timeDebounTot = millis();
        alarmTime -= (1000 * 60);
        if (alarmTime <= 0)
        {
            if (alarmTime == -86400000)
            {
                alarmTime = 0; //Deleting overflow possibilities
            }
            alarmHours = floor(alarmTime / 1000 / 60 / 60);
            int tmpAlarmTime = alarmTime - (alarmHours * 60 * 60 * 1000);
            alarmMinutes = floor(tmpAlarmTime / 1000 / 60);
            Serial.println("ciao2");
            Serial.println(alarmMinutes);
            if (alarmMinutes == 0)
            {
                alarmMinutes = 60;
                if (alarmHours == 0)
                {
                    alarmHours = 23;
                }
                else
                {
                    alarmHours++;
                }
                
            }
            displaySeg(23 - abs(alarmHours), 60 - abs(alarmMinutes), ALARM);
            alarmHours = 23 - abs(alarmHours);
            alarmMinutes = 60 - abs(alarmMinutes);
        }
        else
        {
            alarmHours = floor(alarmTime / 1000 / 60 / 60);
            int tmpAlarmTime = alarmTime - (alarmHours * 60 * 60 * 1000);
            alarmMinutes = floor(tmpAlarmTime / 1000 / 60);
            if (alarmMinutes == 60)
            {
                alarmMinutes = 0;
            }
            displaySeg(alarmHours, alarmMinutes, ALARM);
        }
        stopAlarm = 1;
    }
    else if (digitalRead(BTN_OK) == 0 && timeDeboun >= 175)
    {
        timeDebounTot = millis();
        stopAlarm = 0;
        setAlarm = 0;
    }
}