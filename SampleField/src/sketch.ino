void setup(){
	//Start the serial communications
	Serial.begin(115200);

	//Initialize all the inputs for the buttons
	for(int i=0; i<8; i++) {
		pinMode(i, INPUT_PULLUP);
	}
}

void loop(){
	uint8_t availabilityByte = 0;
	//Fill the bitfield
	for(int i=0; i<8; i++) {
		availabilityByte |= (!digitalRead(i) << i);
	}
	//Send the bitfield
	Serial.write(availabilityByte);
	//Only update every so often
	delay(500);
}
