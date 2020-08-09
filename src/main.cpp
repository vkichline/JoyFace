#include <M5Stack.h>
#include <JoyFace.h>

JoyFace   joy;


void draw_reading(JF_Reading& data) {
  M5.Lcd.drawRect(20,  50, 280, 150, WHITE);   // Outline
  M5.Lcd.drawLine(80,  50,  80, 200, WHITE);  // Vertical sep
  M5.Lcd.drawLine(20,  95, 300,  95, WHITE);  // Crossbar 1
  M5.Lcd.drawLine(20, 150, 300, 150, WHITE);  // Crossbar 2
  M5.Lcd.drawChar('X', 42,  65, 4);
  M5.Lcd.drawChar('Y', 43, 115, 4);
  M5.Lcd.drawChar('B', 43, 165, 4);
  M5.Lcd.drawNumber(data.x, 100,  65, 4);
  M5.Lcd.drawNumber(data.y, 100, 115, 4);
  M5.Lcd.drawString(data.button ? "True  " : "False", 100, 165, 4);
}


void setup() {
  M5.begin();
  joy.begin();
  M5.Lcd.clear();
  M5.Lcd.drawCentreString("JoyFace Test", 160, 12, 4);
  M5.Lcd.drawCentreString("Calibrate", 60, 220, 2);
}


void loop() {
  JF_Reading  reading;

  M5.update();
  if(M5.BtnA.wasReleased()) {
    if(joy.is_calibrating()) {
      joy.read(reading);  // This will change JoyFace into non-calibrating mode
      M5.Lcd.drawCentreString("Calibrate", 60, 220, 2);
    }
    else {
      joy.calibrate();  // This will change JoyFace into calibrating mode.
      M5.Lcd.drawCentreString("  Normal  ", 60, 220, 2);
    }
  }
  if(joy.is_calibrating()) {
    if(joy.calibrate()) {
      M5.Lcd.drawCentreString("Calibrate", 60, 220, 2);
    }
  }
  else if(joy.read(reading)) {
    draw_reading(reading);
  }
  delay(50);
}
