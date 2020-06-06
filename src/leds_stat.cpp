#include "leds_stat.h"

const int LED_COUNT = 300;
const int DATA_PIN = 22;
const int CHANNEL = 0;
SmartLed leds( LED_WS2812, LED_COUNT, DATA_PIN, CHANNEL, DoubleBuffer );



void showRgb(uint8_t r, uint8_t g, uint8_t b) {
	for (int i=0; i<LED_COUNT; i++)
    leds[ i ] = Rgb{ r, g, b };
    leds.show();
}

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