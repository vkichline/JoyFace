#include <M5Stack.h>
#include <Wire.h>
#include "JoyFace.h"

#define FACE_JOY_ADDR 0x5e


void JoyFace::begin(bool show_leds) {
  this->show_leds = show_leds;
  Wire.begin();
  go_dark();    // unconditionally turn leds off
}


bool JoyFace::read(JF_Reading& reading) {
  Wire.requestFrom(FACE_JOY_ADDR, 5);
  if (Wire.available()) {
    calibrating = false;
    // Acquire the joystick data
    uint8_t y_low   = Wire.read();
    uint8_t y_high  = Wire.read();
    uint8_t x_low   = Wire.read();
    uint8_t x_high  = Wire.read();
    reading.button  = 0 == Wire.read();  // 1 = released, 0 = pressed
    reading.x       = x_high << 8 | x_low;
    reading.y       = y_high << 8 | y_low;
    // provide feedback by lighting the corresponding LEDs
    if(show_leds) {
      if(reading.button) {
        set_led(0, 50, 0, 0);
        set_led(1, 50, 0, 0);
        set_led(2, 50, 0, 0);
        set_led(3, 50, 0, 0);
      }
      else {
        if     (reading.x > 600) { set_led(2, 0, 0, 50); set_led(0, 0, 0, 0); }
        else if(reading.x < 400) { set_led(0, 0, 0, 50); set_led(2, 0, 0, 0); }
        else                     { set_led(0, 0, 0,  0); set_led(2, 0, 0, 0); }
        if     (reading.y > 600) { set_led(3, 0, 0, 50); set_led(1, 0, 0, 0); }
        else if(reading.y < 400) { set_led(1, 0, 0, 50); set_led(3, 0, 0, 0); }
        else                     { set_led(1, 0, 0,  0); set_led(3, 0, 0, 0); }
      }
    }
    return true;
  }
  return false;
}


void JoyFace::go_dark() {
  set_led(0, 0, 0, 0);
  set_led(1, 0, 0, 0);
  set_led(2, 0, 0, 0);
  set_led(3, 0, 0, 0);
}


void JoyFace::set_led(int index, int r, int g, int b) {
  Wire.beginTransmission(FACE_JOY_ADDR);
  Wire.write(index);
  Wire.write(r);
  Wire.write(g);
  Wire.write(b);
  Wire.endTransmission();
}


void JoyFace::flash_leds() {
  for (int i = 0; i < 256; i++) {
    Wire.beginTransmission(FACE_JOY_ADDR);
    Wire.write(i % 4);
    Wire.write(random(256) * (256 - i) / 256);
    Wire.write(random(256) * (256 - i) / 256);
    Wire.write(random(256) * (256 - i) / 256);
    Wire.endTransmission();
    delay(2);
  }
  go_dark();
}


void JoyFace::calibrate() {
  Wire.requestFrom(FACE_JOY_ADDR, 5);
  if (Wire.available()) {
    calibrating = true;
  }
}
