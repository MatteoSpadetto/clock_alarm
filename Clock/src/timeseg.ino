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
#include "timeseg.h"
#include "buttons.h"

//Displaying hours and minutes
void displaySeg(int hh, int mm, int mode)
{
    switch (mode)
    {
    case TIME:
        storeLocalTime(); //Storing local date and time
        if (setAlarm == 0)
        {
            display.showNumberDecEx(hh, 0x40, true, 2, 0); //Displaying hours
            display.showNumberDecEx(mm, 0, true, 2, 2);    //Displaying minutes
        }
        break;
    case ALARM:
        if (setAlarm == 1)
        {
            display.showNumberDecEx(hh, 0x40, true, 2, 0); //Displaying hours
            display.showNumberDecEx(mm, 0, true, 2, 2);    //Displaying minutes
        }
        break;
    default:
        display.clear();
        break;
    }
}