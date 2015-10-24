#include <Arduino.h>

void setup();
void loop();
#line 1 "src/robot.ino"

void setup(){
  Serial3.begin(115200);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
}

void loop(){
  while (true){
    byte b = Serial3.read();
    Serial.println(b,HEX);
  }
}
