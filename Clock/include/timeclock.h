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

#ifndef _TIMECLOCK_H
#define _TIMECLOCK_H

#include <Arduino.h>
#include "time.h"

#define TIME_UPDATE 120000


int stopAlarm = 1;

int prevMillis = 0;
int hoursMillis = 0;
int minutesMillis = 0;
int secondsMillis = 0;
int tmpMillis = 0;
int timeMillis = 0;

int hours;
int minutes;
int seconds;
char timeHoursBuff[50];   //Hour char buffer
char timeMinutesBuff[50]; //Minutes char buffer
char timeSecondsBuff[50]; //Seconds char buffer

int firstConn = 0; //To get time for first time

int alarmTime;    //To set alarm time
int alarmHours;   //Alarm hours
int alarmMinutes; //Alarm minutes

const long gmtOffset_sec = 3600;         //GMT offset
const int daylightOffset_sec = 3600;     //Difference in hours between daylight saving time and regular time
const char *ntpServer = "ntp1.inrim.it"; //INRIM Turin NTP server ntp1.inrim.it

struct tm timeinfo; //Time struct

void initTime();       //Initialize date and time NTP server
void storeLocalTime(); //Storing local date and time
void playAlarm();

#endif