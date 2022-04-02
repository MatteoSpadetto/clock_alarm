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

#ifndef _PIXEL_H
#define _PIXEL_H

#include <Arduino.h>
#include <FastLED.h>

#define NUMPIXELS 64   //Number of led in NeoPixels matrix
#define PINPIXELS 15   //Pin connected to the NeoPixels
#define DELAYALARM 500 //Time to pause between pixels alarm colors

#define PIXEL_IMU 0
#define PIXEL_MOON 1
#define PIXEL_SUN 2
#define PIXEL_OFF 3

#define PIXEL_ALARM_ON 4
#define PIXEL_ALARM_OFF 5

int red;   //Initializing RED variable
int green; //Initializing GREEN variable
int blue;  //Initializing BLUE variable
int lum;

CRGB leds[NUMPIXELS]; //Initializing leds

void pixelSetFullRGB(int r, int g, int b); //Full matrix one color setter
void pixelMode(int mode);                  //Pixel's modes and animations

#endif