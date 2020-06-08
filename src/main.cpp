#include <Arduino.h>
#include "JeeUI2.h" // Подключаем JeeUI2 фреймворк к проекту
#include "mylib.h"
#include "leds_stat.h"
#include "modes.h"
#include <tcs3200.h> 
#include <WiFi.h> 
#include <analogWrite.h>
#include "interface.h"  // в этот файл вынесена работа с параметрами и с веб интерфейсом

#define LED_PIN 2


jeeui2 jee; // Создаем объект класса для работы с JeeUI2 фреймворком

void mqttCallback(String topic, String payload);
void onConnect();
void led(bool);
void sendData();
void led_single(int);
void man_mode(String);
void showRgb(uint8_t, uint8_t, uint8_t);

void setup() {
	DMX::Initialize();
	lcd.begin(16, 4);
	lcd.setCursor(0,1);
	lcd.print("STARTING SYSTEM");
	lcd.setCursor(3,2);
	lcd.print("STARTING AP");
	analogWriteResolution(LED_PIN, 12);
	Serial.begin(115200);
	WiFi.softAPConfig(IPAddress(192,168,8,100), IPAddress(192,168,8,1), IPAddress(255,255,255,0));
	jee.mqtt("mqtt.by", 1883, "developer", "8kjdtz6d", mqttCallback, onConnect,  true); // суперфункция, обеспечит всю работу с mqtt, последний аргумент - разрешение удаленного управления
	jee.udp(); // Ответ на UDP запрс. port 4243
	jee.led(10, false); // назначаем пин на светодиод, который нам будет говорит о состоянии устройства. (быстро мигает - пытается подключиться к точке доступа, просто горит (или не горит) - подключен к точке доступа, мигает нормально - запущена своя точка доступа)
	jee.ap(5000); // если в течении 20 секунд не удастся подключиться к Точке доступа - запускаем свою (параметр "wifi" сменится с AP на STA)
	parameters(); // создаем параметры (смотрите файл interface.h)
	jee.ui(interface); // обратный вызов - интерфейс (смотрите файл interface.h)
	jee.update(update); // обратный вызов - вызывается при введении данных в веб интерфейс, нужна для сравнения значений пременных с параметрами  (смотрите файл interface.h)
	jee.begin(true); // Инициализируем JeeUI2 фреймворк. Параметр bool определяет, показывать ли логи работы JeeUI2 (дебаг)
	update(); // 'этой функцией получаем значения параметров в переменные  (смотрите файл interface.h)
}

void loop() {
	jee.handle(); // цикл, необходимый фреймворку
	analogWrite(LED_PIN, Single);
	EXEC_TIMER_SET(100,showRgb(Red, Green, Blue); delay(10););
	WORK(MODE);
}

void onConnect(){ // функция вызывается при подключении к MQTT 
	// тут пользовательские подписки
  	Serial.println("Connected to mqtt");
	//   jee.subscribe("custom"); // подписка на произвольный топик результат - подписка на топик ID/custom
}

void mqttCallback(String topic, String payload){ // функция вызывается, когда приходят данные MQTT 
	// тут пользовательская обработка входящих mqtt сообщений
  	Serial.println("Message [" + topic + " - " + payload + "] ");
}


