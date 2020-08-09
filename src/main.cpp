#include <M5Stack.h>
#include <JoyFace.h>

// JoyFace Calibrator; and application for setting reasonable calibration settings
// for the M5Stack JoyStick FACE module.
// By Van Kichline, in the year of the plague.
//
// There are two parts to calibration: discovering the center point, and discovering the minimax of X and Y.
// Begin by calibrating the center position: place the M5 on a flat surface, make sure the joystick is centered,
// then press the A button. Tap the device a couple times to jiggle the center position a tiny bit. The "+" reading
// will turn green when the center is acquired.
// Next, gently move the joystick in circles to allow calibration to determine the minimums and maximums for X and Y.
// When X and Y turn green, Button A's name will change back from "Normal" to "Calibrate" and the text will turn white.
// Try the settings out. Make sure it's relatively easy to get to 0/0 at rest, and that the extremes attain +/- 100.
// If the calibration looks good to you, press button B in the JoyFace app to save it to NVS.


JoyFace   joy;


void draw_reading(JF_Reading& data) {
  String str;
  M5.Lcd.drawRect(20,  50, 280, 150, WHITE);  // Outline
  M5.Lcd.drawLine(80,  50,  80, 200, WHITE);  // Vertical sep
  M5.Lcd.drawLine(20,  95, 300,  95, WHITE);  // Crossbar 1
  M5.Lcd.drawLine(20, 150, 300, 150, WHITE);  // Crossbar 2
  M5.Lcd.drawChar('X', 42,  65, 4);
  M5.Lcd.drawChar('Y', 42, 115, 4);
  M5.Lcd.drawChar('B', 42, 165, 4);
  str = String(data.x) + "          ";
  M5.Lcd.drawString(str, 100,  65, 4);
  str = String(data.y) + "          ";
  M5.Lcd.drawString(str, 100, 115, 4);
  M5.Lcd.drawString(data.button ? "True  " : "False", 100, 165, 4);
}


// Draw numbers in red if more calibation data is needed, green if complete.
//
void draw_calibration(JF_CalIn& data) {
  String str;
  M5.Lcd.drawRect(20,  50, 280, 150, WHITE);  // Outline
  M5.Lcd.drawLine(80,  50,  80, 200, WHITE);  // Vertical sep
  M5.Lcd.drawLine(20,  95, 300,  95, WHITE);  // Crossbar 1
  M5.Lcd.drawLine(20, 150, 300, 150, WHITE);  // Crossbar 2
  M5.Lcd.drawChar('X', 42,  65, 4);
  M5.Lcd.drawChar('Y', 42, 115, 4);
  M5.Lcd.drawChar('+', 46, 165, 4);
  M5.Lcd.setTextColor(data.xy_count < CALIBRATION_SAMPLES ? RED : GREEN, BLACK);
  str = String(data.min_x) + "/" + String(data.max_x);
  M5.Lcd.drawString(str, 100,  65, 4);
  str = String(data.min_y) + "/" + String(data.max_y);
  M5.Lcd.drawString(str, 100, 115, 4);
  M5.Lcd.setTextColor(data.center_count < CALIBRATION_SAMPLES ? RED : GREEN, BLACK);
  str = String(data.x_center / data.center_count) + "/" + String(data.y_center / data.center_count);
  M5.Lcd.drawString(str, 100, 165, 4);
  M5.Lcd.setTextColor(WHITE, BLACK);
}


void clear_calibration_display() {
  M5.Lcd.fillRect(21,  51, 279, 149, BLACK);  // Erase
  M5.Lcd.drawRect(20,  50, 280, 150, WHITE);  // Outline
  M5.Lcd.drawLine(80,  50,  80, 200, WHITE);  // Vertical sep
  M5.Lcd.drawLine(20,  95, 300,  95, WHITE);  // Crossbar 1
  M5.Lcd.drawLine(20, 150, 300, 150, WHITE);  // Crossbar 2
}


void setup() {
  M5.begin();
  joy.begin();
  M5.Lcd.clear();
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.drawCentreString("JoyFace Calibrator", 160, 12, 4);
  M5.Lcd.drawCentreString("Calibrate",           62, 220, 2);
  M5.Lcd.drawCentreString("Save",               160, 220, 2);
  M5.Lcd.drawCentreString("Clear",              256, 220, 2);
}


void loop() {
  JF_Reading  reading;

  M5.update();
  if(M5.BtnA.wasReleased()) {
    clear_calibration_display();
    if(joy.is_calibrating()) {
      joy.read(reading);  // This will change JoyFace into non-calibrating mode
      M5.Lcd.drawCentreString("Calibrate", 62, 220, 2);
    }
    else {
      joy.calibrate();  // This will change JoyFace into calibrating mode.
      M5.Lcd.drawCentreString("  Normal  ", 62, 220, 2);
    }
  }
  if(M5.BtnB.wasReleased()) {
    joy.save_calibration_to_nvs();
  }
  if(M5.BtnC.wasReleased()) {
    joy.delete_calibration_from_nvs();
  }

  if(joy.is_calibrating()) {
    if(joy.calibrate()) {
      // Calibration is complete, is_calibrating will be false
      draw_calibration(joy.get_calibration_info());
      delay(500);   // to make sure the green numbers show up for both
      clear_calibration_display();
      M5.Lcd.drawCentreString("Calibrate", 62, 220, 2);
    }
    else {
      // More calibration to do
      draw_calibration(joy.get_calibration_info());
    }
  }
  else if(joy.read(reading)) {
    draw_reading(reading);
  }
  delay(50);
}
