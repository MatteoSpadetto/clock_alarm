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
#include "buzzer.h"
#include "pixel.h"

int pixelAlarmMode = PIXEL_ALARM_ON;

//Playing one beat
void playOneBeat(int note, int duration)
{

  ledcWriteTone(LEDC_CHANNEL_0, 0); //Play note 0 on BUZZERPIN to stop the previous one
  //delay(50);                        //Enough to ear the stop
  if (note > 0)
  {
    ledcWriteTone(LEDC_CHANNEL_0, note); //Play note on BUZZERPIN
  }
  pixelMode(pixelAlarmMode);
  if (pixelAlarmMode == PIXEL_ALARM_ON)
  {
    pixelAlarmMode = PIXEL_ALARM_OFF;
  }
  else
  {
    pixelAlarmMode = PIXEL_ALARM_ON;
  }
}

//Playing the full song sections
void playTone(int mode)
{
  unsigned long currentMillis = millis(); //Timer to not stop the tasks running in "main.ino" loop
  if (currentMillis - previousMillis >= duration)
  {
    previousMillis = currentMillis;
    switch (mode)
    {
    case 0: //RingBell tones
      if (indexBeat <= toneNum5)
      {
        duration = beats5[indexBeat];
        playOneBeat(melody5[indexBeat], duration);
      }

      if (indexBeat == toneNum5)
      {
        indexBeat = 0;
      }
      else
      {
        indexBeat++;
      }
      break;

    case 1: //Imperial March tones
      if (indexBeat > toneNum2 + toneNum3 + toneNum2 + toneNum1)
      {
        duration = beats4[indexBeat - toneNum2 - toneNum3 - toneNum2 - toneNum1];
        playOneBeat(melody4[indexBeat - toneNum2 - toneNum3 - toneNum2 - toneNum1], duration);
      }

      else if (indexBeat > toneNum3 + toneNum2 + toneNum1)
      {
        duration = beats2[indexBeat - toneNum3 - toneNum2 - toneNum1];
        playOneBeat(melody2[indexBeat - toneNum3 - toneNum2 - toneNum1], duration);
      }

      else if (indexBeat > toneNum2 + toneNum1)
      {
        duration = beats3[indexBeat - toneNum2 - toneNum1];
        playOneBeat(melody3[indexBeat - toneNum2 - toneNum1], duration);
      }

      else if (indexBeat > toneNum1)
      {
        duration = beats2[indexBeat - toneNum1];
        playOneBeat(melody2[indexBeat - toneNum1], duration);
      }

      else if (indexBeat <= toneNum1)
      {
        duration = beats1[indexBeat];
        playOneBeat(melody1[indexBeat], duration);
      }

      if (indexBeat == toneNum1 + toneNum2 + toneNum3 + toneNum2 + toneNum4)
      {
        indexBeat = 0;
      }
      else
      {
        indexBeat++;
      }
      break;

    default:

      break;
    }
  }
}