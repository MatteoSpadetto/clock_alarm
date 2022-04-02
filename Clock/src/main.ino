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
#include <Adafruit_NeoPixel.h>
#include <TM1637Display.h>
#include <Wire.h>
#include <FastLED.h>
#include "WiFi.h"
#include "debug.h"
#include "buzzer.h"
#include "pixel.h"
#include "buttons.h"
#include "timeseg.h"
#include "connection.h"
#include "timeclock.h"
#include "imu.h"

//TODO: on/off alarm

void setup()
{
  //INITIALIZE debug serial port
  Serial.begin(9600);
  //INITIALIZE matrix with "FastLED.h"
  FastLED.addLeds<NEOPIXEL, 15>(leds, NUMPIXELS);
  //INITIALIZE I2C for IMU reading
  IMUI2CInit();
  //INITIALIZE 7-segment display brightness
  display.setBrightness(0x0a);
  //INITIALIZE buzzer pin mode
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
  ledcAttachPin(BUZZERPIN, LEDC_CHANNEL_0);
  //INITIALIZE buttons --> (pin, function, mode)
  pinMode(buttonPlus.PIN, INPUT);
  pinMode(buttonMinus.PIN, INPUT);
  pinMode(buttonOk.PIN, INPUT);
  //INITIALIZE WiFi
  initWiFi();
  //INITIALIZE time reading from ntp-server Turin INRIM
  initTime();
}

void loop()
{
  imuColorSet();
  switch (mode)
  {
  case PIXEL_IMU:
    pixelMode(PIXEL_IMU);
    displaySeg(hours, minutes, TIME);

    break;
  case PIXEL_MOON:
    pixelMode(PIXEL_MOON);
    displaySeg(hours, minutes, TIME);

    break;
  case PIXEL_SUN:
    pixelMode(PIXEL_SUN);
    displaySeg(hours, minutes, TIME);

    break;
  case PIXEL_OFF:
    pixelMode(PIXEL_OFF);
    display.clear();
    break;

  default:
    break;
  }
  onButtonClick();
  playAlarm();
  if (millis() - setAlarmPeriod >= SET_ALARM_TIMEOUT)
  {
    setAlarm = 0;
  }
}