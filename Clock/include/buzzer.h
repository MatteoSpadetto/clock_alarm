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

#ifndef _BUZZER_H
#define _BUZZER_H

#include <Arduino.h>

#define BUZZERPIN 12

#define LEDC_CHANNEL_0 0    //Using first channel of 16 channels (starting from zero)
#define LEDC_TIMER_8_BIT 8  //Using 13 bit precission for LEDC timer
#define LEDC_BASE_FREQ 2000 //Using 2000 Hz as a LEDC base frequency

#define TONE_MODE 0 //Mode0 = RINGBELL Melody || Mode1 = IMPERIAL MARCH Melody

//Notes for melodies
#define __C 261
#define __D 294
#define __E 329
#define __F 349
#define __G 391
#define __GS 415
#define __A 440
#define __AS 455
#define __B 466
#define __CH 523
#define __CSH 554
#define __DH 587
#define __DSH 622
#define __EH 659
#define __FH 698
#define __FSH 740
#define __GH 784
#define __GSH 830
#define __AH 880

int duration = 0;  //Notes duration
int indexBeat = 0; //Index of the current beat
unsigned long previousMillis = 0;

//Melody for IMPERIAL MARCH
static int melody1[] = {__A, __A, __A, __F, __CH, __A, __F, __CH, __A, 0, __EH, __EH, __EH, __FH, __CH, __GS, __F, __CH, __A, 0};
static int beats1[] = {500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 500, 500, 500, 350, 150, 500, 350, 150, 650, 500};
static int toneNum1 = 19;

static int melody2[] = {__AH, __A, __A, __AH, __GSH, __GH, __FSH, __FH, __FSH, 0, __AS, __DSH, __DH, __CSH, __CH, __B, __CH, 0};
static int beats2[] = {500, 300, 150, 500, 325, 175, 125, 125, 250, 325, 250, 500, 325, 175, 125, 125, 250, 350};
static int toneNum2 = 18;

static int melody3[] = {__F, __GS, __F, __A, __CH, __A, __CH, __EH, 0};
static int beats3[] = {250, 500, 350, 125, 500, 375, 125, 650, 500};
static int toneNum3 = 9;

static int melody4[] = {__F, __GS, __F, __CH, __A, __F, __CH, __A, 0};
static int beats4[] = {250, 500, 375, 125, 500, 375, 125, 650, 650};
static int toneNum4 = 9;

//Melody for RINGBELL
static int melody5[] = {__A, 0};
static int beats5[] = {500, 500};
static int toneNum5 = 2;

void playOneBeat(int note, int duration); //Playing one beat
void playTone(int mode);                  //Playing the full song sections

#endif