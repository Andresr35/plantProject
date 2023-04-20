//#define DEBUG
#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h> // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h> // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include "RTClib.h"
#include <avr/pgmspace.h>

RTC_DS3231 rtc;
const unsigned char waterbucket []PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xf0, 0x00, 0x3c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x78,
  0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x38, 0x00, 0xf0, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1c, 0x3c, 0x00, 0xe0, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x1c, 0x01, 0xe0, 0x1c, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x70, 0x1c, 0x3f, 0xf8, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x1d,
  0xff, 0xff, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0xff, 0xff,
  0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xe0, 0x1f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x70, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x70, 0x7f,
  0xff, 0xff, 0xff, 0x80, 0x1e, 0x3f, 0x80, 0x00, 0x78, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x3f, 0x00,
  0x00, 0x00, 0x3c, 0xff, 0xff, 0xff, 0xff, 0x80, 0x3f, 0x80, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff,
  0xff, 0x00, 0x3f, 0xc0, 0x0e, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xcf, 0x07, 0x80,
  0x0f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x1f, 0xc7, 0xc3, 0xc0, 0x07, 0xff, 0xff, 0xff, 0xfe, 0x00,
  0x3f, 0xe1, 0xc3, 0x80, 0x07, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xe0, 0xc0, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xfe, 0x01, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xe7, 0xc0,
  0x04, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xc3, 0x83, 0x06, 0x00, 0x1f, 0xff, 0xff, 0xff,
  0xfc, 0x7f, 0x00, 0x01, 0x87, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf9, 0xfe, 0x00, 0x01, 0xc3, 0x80,
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xc3, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0x00, 0x01, 0xc1, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff,
  0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff,
  0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xc0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

const unsigned char settinglogo []PROGMEM = {
  0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x00, 0x00, 0x00,
  0x00, 0x83, 0x00, 0x00, 0x00, 0xc0, 0x81, 0x03, 0x00, 0x01, 0xe3, 0x81, 0xc7, 0xc0, 0x03, 0x3f,
  0x81, 0xfc, 0xe0, 0x06, 0x1c, 0x00, 0x38, 0x60, 0x0c, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00,
  0x00, 0x30, 0x06, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0xff, 0x00,
  0xc0, 0x03, 0x01, 0xe7, 0x80, 0xc0, 0x06, 0x03, 0x00, 0xc0, 0x60, 0x06, 0x06, 0x00, 0x60, 0x60,
  0x7e, 0x0c, 0x00, 0x30, 0x7e, 0xf0, 0x0c, 0x00, 0x30, 0x0f, 0xc0, 0x0c, 0x00, 0x30, 0x03, 0xc0,
  0x08, 0x00, 0x10, 0x03, 0xc0, 0x08, 0x00, 0x10, 0x03, 0xc0, 0x0c, 0x00, 0x30, 0x03, 0xe0, 0x0c,
  0x00, 0x30, 0x0f, 0x7e, 0x0c, 0x00, 0x30, 0x7e, 0x06, 0x06, 0x00, 0x60, 0x60, 0x06, 0x03, 0x00,
  0xc0, 0x60, 0x03, 0x01, 0xe7, 0x80, 0xc0, 0x03, 0x00, 0xff, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
  0xe0, 0x06, 0x00, 0x00, 0x00, 0x60, 0x0c, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x00, 0x30,
  0x06, 0x1c, 0x00, 0x38, 0x60, 0x03, 0x3f, 0x81, 0xfc, 0xc0, 0x01, 0xf3, 0x81, 0xcf, 0x80, 0x00,
  0xc0, 0x81, 0x03, 0x00, 0x00, 0x00, 0xc3, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00
};

const unsigned char lightbulblogo []PROGMEM = {
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x07, 0x00,
  0x00, 0xe0, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x70, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x38, 0x00, 0x00,
  0x38, 0x00, 0x00, 0x10, 0x0f, 0xe0, 0x10, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00,
  0xe7, 0xfe, 0x00, 0x00, 0x00, 0x01, 0x87, 0xff, 0x00, 0x00, 0x00, 0x03, 0x0f, 0xff, 0x80, 0x00,
  0x00, 0x06, 0x1f, 0xff, 0xc0, 0x00, 0x00, 0x04, 0x7f, 0xff, 0xc0, 0x00, 0x00, 0x0c, 0x7f, 0xff,
  0xe0, 0x00, 0x00, 0x0c, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x08, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x19,
  0xff, 0xff, 0xf0, 0x00, 0x7f, 0x1f, 0xff, 0xff, 0xf1, 0xfc, 0x2e, 0x1f, 0xff, 0xff, 0xf0, 0xe8,
  0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff,
  0xe0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x07,
  0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x38, 0x7f, 0xfc,
  0x38, 0x00, 0x00, 0x70, 0x3f, 0xf8, 0x1c, 0x00, 0x00, 0xe0, 0x3f, 0xf8, 0x0e, 0x00, 0x01, 0xc0,
  0x1f, 0xf0, 0x07, 0x00, 0x00, 0x80, 0x1f, 0xf0, 0x02, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00
};


Adafruit_FT6206 ctp = Adafruit_FT6206();
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

//Initialize any other variables here
#define MINPRESSURE 10
#define MAXPRESSURE 1000
const int sensorPin1 = 23;
const int sensorPin2 = 24;
const int sensorPin3 = 25;
const int sensorPin4 = 26;
const int ledPin = 28;
const int ledPin2 = 30;
const int ledPin3 = 32;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

char currentPage;
char *TOD[] = {"AM", "PM"};
int hours[] = {12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int i = 8;
int j = 0;
int k = 2;
int l = 0;
int prevl = 0;
int prevj = 0;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int hoursOT;
int prevHour;
int minuteOT;
int prevMinute;
char *AMPM;
char *PrevAMPM;
int CurrDay;
int PrevDay;
int turnOFF;
int BM = 0;
const int rotation = 1; //(0->3)

void setup() {                                                              // old setup
  tft.begin();
  ctp.begin();
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  tft.setRotation(rotation);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  currentPage = '0';
  drawHomeScreen();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}



void loop() {
  uint16_t x, y;
  if (! ctp.touched()) {
    return;
  }
  TS_Point p = ctp.getPoint();
  if (rotation == 0) {
    x = map(p.x, 240, 0, 0, 240);
    y = map(p.y, 320, 0, 0, 320);
  }

  if (rotation == 1) {
    // p.x, p.y reversed //
    x = map(p.y, 320, 0, 0, 320);
    y = map(p.x, 0, 240, 0, 240);
  }

  if (rotation == 2) {
    x = map(p.x, 0, 240, 0, 240);
    y = map(p.y, 0, 320, 0, 320);
  }

  if (rotation == 3) {
    //  p.x, p.y reversed //
    x = map(p.y, 0, 320, 0, 320);
    y = map(p.x, 240, 0, 0, 240);
  }
  Serial.print("X = "); Serial.print(x);
  Serial.print("\tY = "); Serial.println(y);
  //HomePage
  if (currentPage == '0') {
    //Obtain current time and utilize TimeCheck function to print on screen
    DateTime now = rtc.now();
    if (prevMinute != now.minute()) {
      TimeCheck();
    }

    //Calculate the time at which to turn off the LEDs
    turnOFF = i + k;
    if (turnOFF > 23) {
      turnOFF = turnOFF - 24;
    }

    //Checking if the time is at or within the specified time to turn on the LEDs from 1am - 12pm
    if (now.hour() >= i && TOD[j] == "AM" && l == 0 && now.hour() < turnOFF) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      //Draw light bitmap on homescreen to indicate LED's are turned on; Only do this once so the home screen is
      //not continuously printing the bitmap
      if (BM == 0) {
        tft.drawBitmap(145, 185, lightbulblogo, 47, 50, ILI9341_YELLOW);
      }
      BM = 1;
    }
    //Checking if the time is at or within the specified time to turn on the LEDs from 1pm - 12am
    else if ((now.hour() - 12) >= i && TOD[j] == "PM" && l == 0 && (now.hour() - 12) < turnOFF) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      if (BM == 0) {
        tft.drawBitmap(145, 185, lightbulblogo, 47, 50, ILI9341_YELLOW);
      }
      BM = 1;
    }

    //If time of day equals the turn off LED time then shut off LEDs.
    //*Important to mention that this section only works for LEDs turning on during the day and the timer
    //does not run past midnight.The code will need to be adjusted should you want your LEDs to be on overnight*
    //Note: This works if the LED turn on time is set in the AM
    if (now.hour() == turnOFF && TOD[j] == "AM") {
      tft.fillRect(145, 185, 47, 50, ILI9341_BLACK);
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      BM = 0;
    }
    //Note: This works if the LED turn on time is set in the PM
    else if (now.hour() - 12 == turnOFF && TOD[j] == "PM") {
      tft.fillRect(145, 185, 47, 50, ILI9341_BLACK);
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      BM = 0;
    }

    //Get location of screen touch
    TS_Point p = ctp.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    //If Water Bucket is Selected --> will take you to the water soil plant screen
    if ((x > 10) && (x < (84))) {
      if ((y > 185) && (y <= (235))) {
        currentPage = '1';
        tft.fillScreen(ILI9341_BLACK);
        drawPlantScreen();
        soilCheck();
      }
    }

    //If Settings is Selected --> will take you to the setting LED timer screen
    if (x > 270 && x < 310) {
      if (y > 185 && y < 235) {
        currentPage = '2';
        tft.fillScreen(ILI9341_BLACK);
        drawSettingScreen();
      }
    }

  }

  //Water Plants Page
  if (currentPage == '1') {
    TS_Point p = ctp.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    //If Back Button Pressed
    if (x > 4 && x < 66) {
      if (y > 10 && y < 37) {

        currentPage = '0';
        tft.fillScreen(ILI9341_BLACK);
        drawHomeScreen();
        TimeCheck();
        BM = 0;
      }
    }
  }

  //Settings Page
  if (currentPage == '2') {
    TS_Point p = ctp.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
        if (x > 110 && x < 135) {
          if (y > 70 && y < 95) {
            tft.fillRect(195, 72, 35, 30, ILI9341_BLACK);
            tft.setCursor(195, 72);
            i = i - 1;
            if (i < 0) {
              i = 11;
            }
            tft.println(hours[i]);
            delay(500);
          }
        }
    //If right ON TIME arrow is pressed
    if (x > 155 && x < 175) {
      if (y > 70 && y < 140) {
        tft.fillRect(195, 72, 35, 30, ILI9341_BLACK);
        tft.setCursor(195, 72);
        i = i + 1;
        if (i > 11) {
          i = 0;
        }
        tft.println(hours[i]);
        delay(500);
      }
    }
    //Change AM or PM
    if (x > 185 && x < 220) {
      if (y > 170 && y < 195) {
        tft.fillRect(235, 72, 40, 30, ILI9341_BLACK);
        tft.setCursor(235, 72);
        j = 1;
        if (prevj == 1) {
          j = 0;
        }
        tft.println(TOD[j]);
        delay(500);
        prevj = j;
      }
    }
    //If left TIMER arrow is pressed
    if (x > 110 && x < 130) {
      if (y > 135 && y < 160) {
        tft.fillRect(195, 137, 35, 40, ILI9341_BLACK);
        tft.setCursor(195, 137);
        k = k - 1;
        if (k == 0) {
          k = 24;
        }
        tft.println(k);
        delay(500);
      }
    }
    //If right TIMER arrow is pressed
    if (x > 155 && x < 175) {
      if (y > 135 && y < 160) {
        tft.fillRect(195, 137, 35, 40, ILI9341_BLACK);
        tft.setCursor(195, 137);
        k = k + 1;
        if (k > 24) {
          k = 1;
        }
        tft.println(k);
        delay(500);
      }
    }

    //Selecting LED OFF Button will hard turn off the LEDs and keep them off
    if (x > 110 && x < 200) {
      if (y > 190 && y < 215) {
        l = 1;
        tft.drawRect(110, 190, 90, 25, ILI9341_RED);
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        if (prevl == 1) {
          tft.drawRect(110, 190, 90, 25, ILI9341_WHITE);
          l = 0;
          if (hoursOT >= i && hoursOT < turnOFF) {
            digitalWrite(ledPin, HIGH);
            digitalWrite(ledPin2, HIGH);
            digitalWrite(ledPin3, HIGH);
          }
        }
        delay(500);
        prevl = l;
      }
    }


    //If Back Button Pressed --> will send back to the main page
    if (x > 0 && x < 60) {
      if (y > 220 && y < 235) {
        currentPage = '0';
        tft.fillScreen(ILI9341_BLACK);
        drawHomeScreen();
        TimeCheck();
        BM = 0;
      }
    }
  }
}

//TimeCheck function obtains current time and date and prints to homescreen of LCD accordingly
void TimeCheck() {
  //Obtain current time information
  DateTime now = rtc.now();
  

  //Convert military time to standard time
  if (now.hour() > 12)
  {
    hoursOT = now.hour() - 12;
  }
  else {
    hoursOT = now.hour();
  }

  //Adjust AM or PM based on current time and check to see if there was a change from AM to PM or vice versa
  if (now.hour() > 11) {
    AMPM = "PM";
    if (PrevAMPM != AMPM) {
      tft.fillRect(265, 47, 40, 40, ILI9341_BLACK);
    }
    tft.setCursor(265, 47);
    tft.setTextSize(3);
    tft.print(AMPM);
  }
  else {
    AMPM = "AM";
    if (PrevAMPM != AMPM) {
      tft.fillRect(265, 47, 40, 30, ILI9341_BLACK);
    }
    tft.setCursor(265, 47);
    tft.setTextSize(3);
    tft.print(AMPM);
  }
  PrevAMPM = AMPM;

  //Check to see if current time is a new hour and correct display accordingly
  tft.setTextSize(7);
  if (prevHour != hoursOT) {
    if (hoursOT < 10) {
      tft.fillRect(45, 20, 80, 50, ILI9341_BLACK);
      tft.setCursor(85, 20);
      tft.print(hoursOT);
    }
    else {
      tft.fillRect(45, 20, 80, 50, ILI9341_BLACK);
      tft.setCursor(45, 20);
      tft.print(hoursOT);
    }
  }
  else {
    if (hoursOT < 10) {
      tft.setCursor(85, 20);
      tft.print(hoursOT);
    }
    else {
      tft.setCursor(45, 20);
      tft.print(hoursOT);
    }
  }
  prevHour = hoursOT;

  //Print colon and current minute
  tft.print(":");
  minuteOT = now.minute();

  //Checks current time and updates screen if new time
  if (prevMinute != minuteOT) {
    tft.fillRect(165, 20, 85, 50, ILI9341_BLACK);
    if (minuteOT < 10) {
      tft.print("0");
      tft.print(minuteOT);
    }
    else {
      tft.print(minuteOT);
    }
  }
  else {
    if (minuteOT < 10) {
      tft.print("0");
      tft.print(minuteOT);
    }
    else {
      tft.print(minuteOT);
    }
  }
  prevMinute = minuteOT;


  //Obtains current day of the week, month, day, and year; Prints to screen and checks to see if there is a new day
  CurrDay = now.day();
  if (CurrDay != PrevDay) {
    tft.fillRect(50, 100, 270, 15, ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setCursor(50, 100);
    tft.print(daysOfTheWeek[now.dayOfTheWeek()]);
    tft.setCursor(180, 100);
    tft.print(now.month());
    tft.print("/");
    tft.print(now.day());
    tft.print("/");
    tft.print(now.year());
  }
  else {
    tft.setTextSize(2);
    tft.setCursor(50, 100);
    tft.print(daysOfTheWeek[now.dayOfTheWeek()]);
    tft.setCursor(180, 100);
    tft.print(now.month());
    tft.print("/");
    tft.print(now.day());
    tft.print("/");
    tft.print(now.year());
  }
  PrevDay = CurrDay;
}

//soilCheck function reads digitial input of soil sensor and indicates which of the 4 plants needs to be watered
//Circles that are filled in solid green indicate that they are dry and neet to be watered.
void soilCheck() {
  buttonState1 = digitalRead(sensorPin1);
  buttonState2 = digitalRead(sensorPin2);
  buttonState3 = digitalRead(sensorPin3); 
  buttonState4 = digitalRead(sensorPin4);
  if (buttonState1 == HIGH) {
    tft.fillCircle(110, 80, 45, ILI9341_GREEN);
  }
  else if (buttonState1 == LOW) {
    tft.fillCircle(110, 80, 44, ILI9341_BLACK);
  }
  if (buttonState2 == HIGH) {
    tft.fillCircle(110, 180, 45, ILI9341_GREEN);
  }
  else if (buttonState2 == LOW) {
    tft.fillCircle(110, 180, 44, ILI9341_BLACK);
  }
  if (buttonState3 == HIGH) {
    tft.fillCircle(232, 80, 45, ILI9341_GREEN);
  }
  else if (buttonState3 == LOW) {
    tft.fillCircle(232, 80, 44, ILI9341_BLACK);
  }
  if (buttonState4 == HIGH) {
    tft.fillCircle(232, 180, 45, ILI9341_GREEN);
  }
  else if (buttonState4 == LOW) {
    tft.fillCircle(232, 180, 44, ILI9341_BLACK);
  }
}

//drawPlantScreen function draws the plant soil screen
void drawPlantScreen() {
  tft.setRotation(1);
  tft.drawRect(89, 4, 164, 27, ILI9341_WHITE);
  tft.fillRect(90, 5, 162, 25, ILI9341_BLUE);
  tft.setCursor(100, 10);
  tft.setTextSize(2.5);
  tft.println("WATER PLANTS");
  tft.drawRect(4, 10, 62, 27, ILI9341_WHITE);
  tft.fillRect(5, 11, 60, 25, ILI9341_BLUE);
  tft.setCursor(15,11);
  tft.setTextSize(3);
  tft.println("<-");
  tft.drawCircle(110, 80, 45, ILI9341_GREEN); 
  tft.drawCircle(110, 180, 45, ILI9341_GREEN);
  tft.drawCircle(232, 80, 45, ILI9341_GREEN);
  tft.drawCircle(232, 180, 45, ILI9341_GREEN);

}

//drawSettingScreen draws the setting screen
void drawSettingScreen() {
  //Draws title "SET LED TIME" and outlines it in a rectangle box
  tft.setRotation(1);
  tft.drawRect(89, 4, 164, 27, ILI9341_WHITE);
  tft.fillRect(90, 5, 162, 25, ILI9341_RED);
  tft.setCursor(100, 10);
  tft.setTextSize(2.5);
  tft.println("SET LED TIME");

  //Draws "ON TIME" as well as left and right arrows
  tft.drawRect(4, 70, 90, 25, ILI9341_WHITE);
  tft.fillRect(5, 71, 88, 23, ILI9341_BLUE);
  tft.setCursor(8, 75);
  tft.println("ON TIME");
  tft.drawRect(110, 70, 20, 25, ILI9341_WHITE);
  tft.fillRect(111, 71, 18, 23, ILI9341_BLUE);
  tft.setCursor(114, 75);
  tft.println("<");
  tft.drawRect(155, 70, 20, 25, ILI9341_WHITE);
  tft.fillRect(156, 71, 18, 23, ILI9341_BLUE);
  tft.setCursor(159, 75);
  tft.println(">");

  //Draws TIMER as well as left and right arrows
  tft.drawRect(4, 135, 90, 25, ILI9341_WHITE);
  tft.fillRect(5, 136, 88, 23, ILI9341_BLUE);
  tft.setCursor(18, 140);
  tft.println("TIMER");
  tft.drawRect(110, 135, 20, 25, ILI9341_WHITE);
  tft.fillRect(111, 136, 18, 23, ILI9341_BLUE);
  tft.setCursor(114, 140);
  tft.println("<");
  tft.drawRect(155, 135, 20, 25, ILI9341_WHITE);
  tft.fillRect(156, 136, 18, 23, ILI9341_BLUE);
  tft.setCursor(159, 140);
  tft.println(">");

  //Checks to see if hard set LED OFF button has been pressed in the past and draws text/rectangle accordingly
  tft.setTextSize(2.5);
  if (l == 1) {
    tft.drawRect(110, 190, 90, 25, ILI9341_RED);
  }
  else {
    tft.drawRect(110, 190, 90, 25, ILI9341_WHITE);
  }
  tft.fillRect(111, 191, 88, 23, ILI9341_BLUE);
  tft.setCursor(114, 195);
  tft.println("LED OFF");

  //Draws "HRS" next to TIMER numbers
  tft.setCursor(235, 137);
  tft.setTextSize(3);
  tft.println("HRS");

  //Draws current TIMER time
  tft.fillRect(195, 137, 35, 30, ILI9341_BLACK);
  tft.setCursor(195, 137);
  tft.println(k);

  //Draws back arrow
  tft.drawRect(4, 208, 62, 27, ILI9341_WHITE);
  tft.fillRect(5, 209, 60, 25, ILI9341_RED);
  tft.setCursor(15, 211);
  tft.setTextSize(3);
  tft.println("<-");

  //Draws current ON TIME time as well as "AM" or "PM"
  tft.fillRect(195, 72, 35, 30, ILI9341_BLACK);
  tft.setCursor(195, 72);
  tft.println(hours[i]);
  tft.fillRect(235, 72, 40, 30, ILI9341_BLACK);
  tft.setCursor(235, 72);
  tft.println(TOD[j]);
}

//drawHomescreen draws the homescreen of the display
void drawHomeScreen() {
  tft.setRotation(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(7);
  tft.fillScreen(ILI9341_BLACK);
  tft.drawBitmap(10, 185, waterbucket, 74, 50, ILI9341_BLUE);
  tft.drawBitmap(270, 190, settinglogo, 40, 40, ILI9341_GREEN);
}
