const int ledPin = 2;  // 16 corresponds to GPIO16

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;


void led(bool k){
	if (k==true) digitalWrite(2, HIGH);
	else digitalWrite(2,LOW);
}



void led_single(int k){
	ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(ledPin, ledChannel);
	ledcWrite(ledChannel, k);
}