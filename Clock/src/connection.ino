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
#include <TM1637Display.h>
#include "WiFi.h"
#include "connection.h"
#include "timeclock.h"
#include "timeseg.h"

//Searching and connecting WiFi
void initWiFi()
{
    for (size_t i = 0; i < sizeof(ssid); i++) //Iterating all saved networks to find one
    {
        WiFi.begin(ssid[i], password[i]); //Searching WiFi network
        Serial.printf("Connecting to %s ", ssid[i]);
        int tmpMillis = millis(); //For WIFI_TIMEOUT
        int flag = 0;
        while (WiFi.status() != WL_CONNECTED && flag == 0) //Waiting for connection until WIFI_TIMEOUT or CONN success
        {
            delay(500);
            Serial.print(".");
            display.showNumberDecEx(0, 0x40, true, 2, 0); //Displaying hours
            display.showNumberDecEx(0, 0, true, 2, 2);
            delay(500);
            display.clear();
            delay(500);
            if (millis() - tmpMillis > WIFI_TIMEOUT)
            {
                flag = 1; //Exiting WHILE to try with another ssid and password
            }
        }
        if (WiFi.status() == WL_CONNECTED) //Stopping connection task
        {
            Serial.println("Connected to WiFi network");
            firstConn = 1;
            break;
        }
        else
        {
            Serial.println("WiFi network not found");
        }
    }
}