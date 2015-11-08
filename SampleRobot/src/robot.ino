#include <BluetoothMaster.h>
#include <ReactorProtocol.h>
#include <LiquidCrystal.h>

#include "Robot.h"

const int debugPin = 22;

Robot *steve;

void setup() {
  Serial.begin(9600);
  pinMode(debugPin, INPUT_PULLUP);
  steve = Robot::getInstance();
  steve->setup();
}


void loop() {
  steve->btClient.readMessage();
  steve->btClient.sendHeartbeat();
  steve->btClient.sendStatus();

  if (steve->carryingSpentRod()){
    steve->btClient.sendLowRadiationAlert();
  }
  else if (steve->carryingNewRod()){
    steve->btClient.sendHighRadiationAlert();
  }

  if (sendDebug()){
    char str[25];
    String complement = randomComplement();
    steve->btClient.sendDebugString("peter is "+complement);
  }
}

bool sendDebug(){
  return !digitalRead(debugPin);
}

String randomComplement(){
  String complements[5];
  complements[0]="awesome";
  complements[1]="cool";
  complements[2]="handsome";
  complements[3]="brilliant";
  complements[4]="humble";
  int index = random(5);
  return complements[index];
}
