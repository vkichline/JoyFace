#pragma once
#include <stdint.h>

// A dirver interface for the Joystick Face Module for M5Stack


typedef struct JF_Reading {
  uint16_t  x;
  uint16_t  y;
  bool      button;
} JF_Reading;


class JoyFace {
  public:
    void  begin(bool show_leds = true);
    bool  read(JF_Reading& reading);
    void  calibrate();
    void  go_dark();
    bool  is_calibrating() { return calibrating; }
  private:
    void  set_led(int index, int r, int g, int b);
    void  flash_leds();
    bool  show_leds   = true;
    bool  calibrating = false;
};
