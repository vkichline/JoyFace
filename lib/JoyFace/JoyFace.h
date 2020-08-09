#pragma once
#include <stdint.h>

// A dirver interface for the Joystick Face Module for M5Stack

#define CALIBRATION_SAMPLES 50    // How many samples required for min/max and center calibation (must be less than 255)

typedef struct JF_Reading {
  int16_t   x;
  int16_t   y;
  bool      button;
} JF_Reading;


typedef struct JF_Calibration_Info {
  void clear() {
    max_x = max_y = x_center = y_center = xy_count = center_count = 0;
    min_x = min_y = 0xFFFF;
    complete      = false;
  }
  uint16_t  min_x         = 0xFFFF; // Smallest X seen while calibrating
  uint16_t  max_x         = 0;      // Smallest Y seen while calibrating
  uint16_t  min_y         = 0xFFFF; // Largest X seen while calibrating
  uint16_t  max_y         = 0;      // Largest Y seen while calibrating
  uint32_t  x_center      = 0;      // Sum of all center samples for X
  uint32_t  y_center      = 0;      // Sum of all center samples for Y
  uint8_t   xy_count      = 0;      // How many X/Y min/max positions have been acquired
  uint8_t   center_count  = 0;      // How many center positions have been acquired
  bool      complete      = false;  // True if 256 at rest positions have been acquired
} JF_Calibration_Info, JF_CalIn;


typedef struct JF_Calibration_Data {
  uint16_t  center_x;
  uint16_t  center_y;
  double    x_scale;
  double    y_scale;
} JF_Calibration_Data, JF_CalDat;


class JoyFace {
  public:
    void      begin(bool show_leds = true);
    bool      read(JF_Reading& reading);
    bool      calibrate();  // returns true when calibation is complete
    void      go_dark();
    bool      is_calibrating()        { return calibrating; }
    bool      is_calibrated()         { return calibrated;  }
    JF_CalIn  &get_calibration_info() { return cal_info;    }
  private:
    void      set_led(int index, int r, int g, int b);
    void      flash_leds();
    bool      show_leds   = true;
    bool      calibrating = false;
    bool      calibrated  = false;
    JF_CalIn  cal_info;
    JF_CalDat cal_data;
};
