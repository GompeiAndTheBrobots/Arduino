#include <BluetoothMaster.h>
#include <ReactorProtocol.h>
#include <LiquidCrystal.h>

#include "Robot.h"

Robot *steve;

void setup() {
  Serial.begin(9600);
  steve = Robot::getInstance();
  steve->setup();
}


void loop() {
  steve->btClient.readMessage();
  steve->btClient.sendHeartbeat();
  steve->btClient.sendRadiationAlert();
}
