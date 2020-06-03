int mqtt_int; // интервал отправки данных по MQTT в секундах 
bool stat_led;
bool toBool(String);
int Red;
int Green;
int Blue;
int Single;
int DMX_ch_r;
int DMX_ch_g;
int DMX_ch_b;
int DMX_ch_s;
String MODE;



void parameters(){
// создаем параметры для нашего проекта
  jee.var("wifi", "STA"); // режим работы WiFi по умолчанию ("STA" или "AP")  (параметр в энергонезависимой памяти)
  jee.var("ssid", "Etereshop_office"); // имя точки доступа к которой подключаемся (параметр в энергонезависимой памяти)
  jee.var("pass", "0164f008"); // пароль точки доступа к которой подключаемся (параметр в энергонезависимой памяти)

  jee.var("led", "0"); 
  jee.var("Red", "0"); 
  jee.var("Green", "0"); 
  jee.var("Blue", "0");
  jee.var("Single", "0");  
  jee.var("DMX_ch_r", "1");  
  jee.var("DMX_ch_g", "2");  
  jee.var("DMX_ch_b", "3");  
  jee.var("DMX_ch_s", "4");  

 }

void update(){ // функция выполняется после ввода данных в веб интерфейсе. получение параметров из веб интерфейса в переменные
  // получаем данные в переменную в ОЗУ для дальнейшей работы
  stat_led = toBool(jee.param("led")); // читаем параметр в переменную с переобразованием в нужный тип данных
  Red = jee.param("Red").toInt();
  Green = jee.param("Green").toInt();
  Blue = jee.param("Blue").toInt();
  Single = jee.param("Single").toInt();
  DMX_ch_r = jee.param("DMX_ch_r").toInt();
  DMX_ch_g = jee.param("DMX_ch_g").toInt();
  DMX_ch_b = jee.param("DMX_ch_b").toInt();
  DMX_ch_s = jee.param("DMX_ch_s").toInt();
  MODE = jee.param("MODE");
  
}

void interface(){ // функция в которой мы формируем веб интерфейс и интерфейс в приложении JeeUI2

  jee.app("Магистратура"); // название программы (отображается в веб интерфейсе)

  // создаем меню
  jee.menu("Режим работы");
  jee.menu("Настройка светодиодов");
  jee.menu("Настройки каналов DMX");
  jee.menu("Настройки MQTT");
  jee.menu("Настройки Wi-Fi");

  jee.page(); // разделитель между страницами
  jee.select("MODE", "Выберете режим управления");
  jee.option("","");
  jee.option("MANUAL","Ручное управление");
  jee.option("DMX","Управление при помощи DMX консоли");
  jee.option("MQTT_serv","Упраление через веб страницу и mqtt сервер");


  jee.page();
  jee.range("Red", 0, 255 , 1, "Уровень красного");
  jee.range("Green", 0, 255 , 1, "Уровень зеленого");
  jee.range("Blue", 0, 255 , 1, "Уровень синего");
  jee.range("Single", 0, 255 , 1, "Уровень яркости одноцетного канала");
  

  jee.page();
  jee.number("DMX_ch_r", "Введите номер канала для чтения DMX красного цвета");
  jee.number("DMX_ch_g", "Введите номер канала для чтения DMX зеленого цвета");
  jee.number("DMX_ch_b", "Введите номер канала для чтения DMX синего цвета");
  jee.number("DMX_ch_s", "Введите номер канала для чтения DMX одноцветной ленты");

  jee.page();
  // Страница "Настройки MQTT"
  jee.formMqtt(); // готовая форма настроек MQTT

  jee.page(); // разделитель между страницами
  // Страница "Настройки WiFi"
  jee.formWifi(); // готовая форма настроек Wi-Fi
  jee.page(); // разделитель между страницами

}