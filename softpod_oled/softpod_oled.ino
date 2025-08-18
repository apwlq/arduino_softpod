#include <Arduino.h>
#include <U8g2lib.h>

#include <Wire.h> // library requires for IIC communication

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // initialization for the used OLED display

const int sensorPin = A0;
int sensorValue = 0;
int numReading = 5;

int pastValue = 0;
int dummy = 0;

int val = 0;


int touch = 0;
int pastTouch = 0;
char scrollStr[5];
char clickStr[5];

void setup() {
  u8g2.begin();
  Serial.begin(9600);
}

void loop() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  
  u8g2.setFont(u8g2_font_t0_18b_tr);
  u8g2.drawStr(1, 15, "ARDUINO TEST");

  u8g2.setFont(u8g2_font_t0_11b_tr);
  u8g2.drawStr(2, 42, "CLICK");
  u8g2.drawStr(2, 30, "SCROLL");
  u8g2.drawStr(2, 54, "Value");

  u8g2.setFont(u8g2_font_t0_11_tr);

  long total = 0;
  for (int i = 0; i < numReading; i++) {
    total += analogRead(sensorPin);
  }
  int average = total / numReading / 4;
  average += 127;
  Serial.print(average);
  // Serial.print(" ");
  if (average == 127) {
    touch = 0;
    strcpy(scrollStr, "ZERO");
    // Serial.println("0");
    dummy = 0;
  } else if (average > pastValue) {
    // Serial.println("-");
    dummy -= 1;
  } else if (average < pastValue) {
    // Serial.println("+");
    dummy += 1;
  } else {
    touch = 1;
    dummy = 0;
  }

  if (dummy > 3) {
    Serial.println("+");
    strcpy(scrollStr, "UP");
    val += 1;
    dummy = 0;
  } 
  if (dummy < -3) {
    Serial.println("-");
    strcpy(scrollStr, "DOWN");
    val -= 1;
    dummy = 0;
  }
  u8g2.drawStr(41, 30, scrollStr);

  if(pastTouch == 1) {
    if (touch == 0) {
      // Serial.println("Touch End");
      strcpy(clickStr, "FALSE");
      touch = 0;
    }
  } else if (pastTouch == 0) {
    if (touch == 1) {
      // Serial.println("Touch Start");
      strcpy(clickStr, "TRUE");
    }
  }
  u8g2.drawStr(41, 42, clickStr);

  char buf[10];
  sprintf(buf, "%d", val);
  u8g2.drawStr(41, 54, buf);
  pastTouch = touch;
  pastValue = average;

  u8g2.sendBuffer();
}
