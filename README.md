# JoyFace
A program to calibrate the JoyStick Panel for M5 FACES and serve as a device drive with NVS persistence

This program allows you to calibrate your joystick FACE. It writes persistent data to memory, so the calibration is automatically loaded on the M5Stack it was saved on.
Results of JoyFace.read() are scaled to -100/+100. The button is inverted so that 'true' means 'pressed.'

## How to Calibrate

* There are two parts to calibration: discovering the center point, and discovering the minimax of X and Y.
* Begin by calibrating the center position: place the M5 on a flat surface, make sure the joystick is centered, then press the A button. Tap the device a couple times to jiggle the center position a tiny bit. The "+" reading will turn green when the center is acquired.
* Next, gently but quickly move the joystick in circles to allow calibration to determine the minimums and maximums for X and Y.
* When X and Y turn green, Button A's name will change back from "Normal" to "Calibrate" and the text will turn white, showing you calibrated readings from the joystick.
* Try the settings out. Make sure it's relatively easy to get to 0/0 at rest, and that the extremes attain +/- 100.
* If the calibration looks good to you, press button B in the JoyFace app to save it to Non-Volatile Storage.
* The settings will be automatically loaded on startup when available.
