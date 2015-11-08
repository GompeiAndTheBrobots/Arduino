#include "BTClient.h"
#include "Robot.h"
#include "Util.h"

BTClient::BTClient() :
  pcol(byte(::TEAM_NUMBER)) {
    supply = -1;
    storage = -1;
}

void BTClient::setup(){
  pinMode(14,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);
  Serial3.begin(115200);
}

void BTClient::sendStatus(){
  byte data[3];
  data[0] = 4;
  data[1] = 2;
  data[2] = 6;
  sendData(STATUS_MSG, data);
}

void BTClient::sendLowRadiationAlert(){
  byte data[3];
  data[0] = 0x2C;
  sendData(RADIATION_MSG, data);
}

void BTClient::sendHighRadiationAlert(){
  byte data[3];
  data[0] = 0xFF;
  sendData(RADIATION_MSG, data);
}

void BTClient::sendHeartbeat(){
  unsigned long t = millis();
  unsigned long dt = t - lastSentHeartbeat;
  if (dt > HEARTBEAT_PERIOD){
    lastSentHeartbeat = t;
    sendData(HEARTBEAT_MSG, NULL);
  }
}

void BTClient::sendDebugString(String str){
  Serial.println(str);
}

void BTClient::sendData(MSG_TYPE type, byte data[3]){
  byte pkt[10];
  pcol.setDst(0x00);
  int sz = pcol.createPkt(type, data, pkt);
  btMaster.sendPkt(pkt, sz);
}

void BTClient::readMessage(){
  byte pkt[10];
  byte rawData[3];
  byte messageType;

  if (btMaster.readPacket(pkt)){
    //don't care about ones not for us
    if (pkt[4] == TEAM_NUMBER || pkt[4] == 0){
      if (pcol.getData(pkt,rawData,messageType)){
        char str[17];
				switch(messageType){
          case STORAGE_MSG:
            storage = rawData[0];
            snprintf(str,17,"sply=%02x stor=%02x",supply,storage);
            Robot::getInstance()->debugPrint(str);
            break;

          case SUPPLY_MSG:
            supply = rawData[0];
            snprintf(str,17,"sply=%i stor=%i",supply,storage);
            Robot::getInstance()->debugPrint(str);
            break;

          case STOP_MSG:
            Robot::getInstance()->paused = true;
            Robot::getInstance()->debugPrint2("stopping");
            break;

          case RESUME_MSG:
            Robot::getInstance()->paused = false;
            Robot::getInstance()->debugPrint2("resuming");
            break;

          default:
            // only these 4 should be sent by field
            Serial.println("other weird msg");
            Robot::getInstance()->debugPrint2("????");
            break;
        }
      }
    }
  }
}

