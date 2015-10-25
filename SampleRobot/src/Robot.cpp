#include "Robot.h"

Robot *Robot::instance = NULL;

Robot::Robot() : lcd(40,41,42,43,44,45) {
  radiating = true;
}

Robot *Robot::getInstance(){
  if (instance == NULL){
    instance = new Robot();
  }
  return instance;
}

void Robot::setup(){
  paused = false;
  lcd.begin(16,2);
  btClient.setup();
}

void Robot::debugPrint2(int i){
  lcd.setCursor(0,1);
  char str[17];
  sprintf(str,"%-6i",i);
  lcd.print(str);
}

void Robot::debugPrint2(char *s){
  lcd.setCursor(0,1);
  char str[17];
  sprintf(str,"%-6s",s);
  lcd.print(str);
}

void Robot::debugPrint(int i){
  lcd.setCursor(0,0);
  char str[17];
  sprintf(str,"%-6i",i);
  lcd.print(str);
}

void Robot::debugPrint(char *s){
  lcd.setCursor(0,0);
  char str[17];
  sprintf(str,"%-6s",s);
  lcd.print(str);
}

