// -*- coding: utf-8 -*-
// @Time    : 2021/12/31 14:27
// @Author  : Tianci
// @Email   : tianci_zhang@tju.edu.cn
// @File    : main.cpp
// @Software: Arduino 1.8.15 or VScode

// all header files and definition
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads; 
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SH1106Wire.h"   // legacy: #include "SH1106.h"
SH1106Wire display(0x3c, SDA, SCL);     // ADDRESS, SDA, SCL
int counter = 1;
int id = 1;
float buff[4];

void displayOLED(int id, float value)
{
  switch (id)
  {
  case (1):
    display.drawString(0, 0, "v");
    display.drawString(5, 0, String(id));
    display.drawString(10, 0, ":");
    display.drawString(15, 0, String(value,5));
    break;

  case (2):
    display.drawString(66, 0, "v");
    display.drawString(71, 0, String(id));
    display.drawString(76, 0, ":");
    display.drawString(81, 0, String(value,5));
    break;
    
  case (3):
    display.drawString(0, 10, "v");
    display.drawString(5, 10, String(id));
    display.drawString(10, 10, ":");
    display.drawString(15, 10, String(value,5));
    break;  

  case (4):
    display.drawString(66, 10, "v");
    display.drawString(71, 10, String(id));
    display.drawString(75, 10, ":");
    display.drawString(81, 10, String(value,5));
    break;    
          
  default:
    break;
  }
}

void setup(void)
{
  //pinMode(34,INPUT); //adc0 in esp32, 12 bit， do not use in this project

  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  Serial.println("Hello! Tianci, Get starting...");

  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
     ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS1115.");
    while (1);
  }
}

void loop(void)
{
  int16_t adc;
  float volts;
  adc = ads.readADC_SingleEnded(id-1);
  volts = 1.00000*ads.computeVolts(adc);
  buff[id-1]=volts;

if(id==4){
  display.clear();
  // draw the current demo method
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  
  displayOLED(1,buff[0]);
  displayOLED(2,buff[1]);
  displayOLED(3,buff[2]);
  displayOLED(4,buff[3]);

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 48, "By ZTC");

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 48, String(millis()));
  // write the buffer to the display
  display.display();
  }

  counter++;
  id++;

  if(id>=5){
    id=1;
    }
  delay(10);
}
