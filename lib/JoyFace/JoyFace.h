#pragma once
#include <stdint.h>

// A dirver interface for the Joystick Face Module for M5Stack

// The JoyStick Face returns quantities roughly between 200 and 800. We don't need to sample other values.
#define CALIBRATION_POS_COUNT   650   // How many counters to allocate for x & y calibation
#define CALIBRATION_OFFSET      200   // Offset from reading to first counter
#define CALIBRATION_POS_SAMPLES 50    // How many samples to require for center calibation (must be less than 255)

typedef struct JF_Reading {
  uint16_t  x;
  uint16_t  y;
  bool      button;
} JF_Reading;


typedef struct JF_Calibration_Data {
  void init() {
    max_x = max_y = xy_count = 0;
    min_x = min_y = 0xFFFF;
    complete      = false;
  }
  uint16_t  min_x       = 0xFFFF; // Smallest X seen while calibrating
  uint16_t  max_x       = 0;      // Smallest Y seen while calibrating
  uint16_t  min_y       = 0xFFFF; // Largest X seen while calibrating
  uint16_t  max_y       = 0;      // Largest Y seen while calibrating
  uint8_t   x_pos[650]  = {0};    // Number of times X was at rest as x_pos+200
  uint8_t   y_pos[650]  = {0};    // Number of times Y was at rest as x_pos+200
  uint8_t   xy_count    = 0;      // How many X/Y positions have been acquired
  bool      complete    = false;  // True if 256 at rest positions have been acquired
} JF_Calibration_Data, JF_CalDat;


class JoyFace {
  public:
    void      begin(bool show_leds = true);
    bool      read(JF_Reading& reading);
    bool      calibrate();  // returns true when calibation is complete
    void      go_dark();
    bool      is_calibrating()        { return calibrating; }
    bool      is_calibrated()         { return calibrated;  }
    JF_CalDat *get_calibration_data() { return data;        }
  private:
    void      set_led(int index, int r, int g, int b);
    void      flash_leds();
    bool      show_leds   = true;
    bool      calibrating = false;
    bool      calibrated  = false;
    JF_CalDat *data       = nullptr;
};
