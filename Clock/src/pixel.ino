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
#include <FastLED.h>
#include "pixel.h"
#include "imu.h"

//Full matrix one color setter
void pixelSetFullRGB(int r, int g, int b)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    leds[i] = CRGB(r, g, b); //Setting RGB color for each pixel
  }
  FastLED.show(); //Sending array leds[] to the matrix
  delay(5);       //Delay in order to have a more stable comunication
}

//Pixel's modes and animations
void pixelMode(int mode)
{
  switch (mode)
  {
  case PIXEL_IMU:
    imuRGB(); //Changing matrix color with IMU (in "imu.h")
    break;

  case PIXEL_MOON: //Full color (100, 0, 100) matrix
    pixelSetFullRGB(255, 250, 235);
    break;
    
  case PIXEL_SUN: //Full color (100, 0, 100) matrix
    pixelSetFullRGB(255, 160, 75);
    break;

  case PIXEL_OFF: //Full color (100, 0, 100) matrix
    pixelSetFullRGB(0, 0, 0);
    break;

  case PIXEL_ALARM_ON: //Full color (100, 0, 100) matrix
    pixelSetFullRGB(MAX_COLOR, 0, MAX_COLOR);
    break;

  case PIXEL_ALARM_OFF: //Full color (100, 0, 100) matrix
    pixelSetFullRGB(MAX_COLOR, MAX_COLOR, 0);
    break;

  default:
    break;
  }
}