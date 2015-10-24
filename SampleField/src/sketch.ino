void setup(){
	Serial.begin(115200);
}

void loop(){
	Serial.write(0b10100101);
	delay(250);
}
