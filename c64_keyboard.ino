
#include <Keyboard.h>
const byte ROWS = 8;
const byte COLS = 8;

byte colPins[COLS] = {23, 22, 21, 20, 19, 18, 17, 16};
byte rowPins[ROWS] = { 15, 14, 13, 12, 11, 10, 9, 8};



void setup() {
  setupPins();
  Keyboard.begin();
  Serial.begin(9600);
}
void loop() {
  press();
}
