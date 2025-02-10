#define solPin A2 // порт для подключения датчика 
int minsol = 200; // минимальное значение влажности почвы 
int sol; 
int so2; 
const int AirValue = 1015;             // Максимальное значение сухого датчика 
const int WaterValue = 350;           // Минимальное значение погруженного датчика 
// ДИСПЛЕЙ 
#include <LCD_1602_RUS.h> 
LCD_1602_RUS lcd(0x27, 20, 4); //инициализация экрана 
// ДАТЧИК ТЕМП И ВЛАЖ 
#include "DHT.h" 
#define DHTPIN 2 
DHT dht(DHTPIN, DHT11); 
//ДАТЧИК ОСВЕЩЕННОСТИ 
int temt6000Pin = A0;   
int light;                              
int light_value;                            
void setup(){ 
  pinMode(12, OUTPUT); 
  pinMode(8, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(4, OUTPUT); 
  Serial.begin(9600);                 
  pinMode(solPin, INPUT);    
  pinMode(A1, OUTPUT); 
  digitalWrite(A1, HIGH); 
  // ДАТЧИК ТЕМП И ВЛАЖ 
  (temt6000Pin, INPUT);    
  dht.begin();     
 // ДИСПЛЕЙ   
 lcd.init();                       
 lcd.backlight();  
 lcd.setCursor(0,0);      
 lcd.print("ВЛАЖНОСТЬ В"); 
 lcd.setCursor(19,0);      
 lcd.print("%"); 
 lcd.setCursor(0,1);      
 lcd.print("ТЕМПЕРАТУРА");    
 lcd.setCursor(19,1);      
 lcd.print("С");  
 lcd.setCursor(0,2);  
 lcd.print("ОСВЕЩЕНИЕ");   
 lcd.setCursor(19,2);      
 lcd.print("%");   
 lcd.setCursor(0,3);  
 lcd.print("ВЛАЖНОСТЬ П");  
 lcd.setCursor(19,3);      
 lcd.print("%");   
} 
void loop() {  
  digitalWrite(12, HIGH); 
if (so2 < 50){ 
  digitalWrite(4,HIGH); 
} 
  else{ digitalWrite(4, LOW); 
} 
if (light < 50){ 
  digitalWrite(7,HIGH); 
} 
  else{ digitalWrite(7, LOW); 
} 
Serial.println(sol);    // Передаем данные последовательную порт 
//ДАТЧИК ОСВЕЩЕННОСТИ НА ДИСПЛЕЙ 
light_value = analogRead(temt6000Pin);       // Считывает показания с вывода 
light = light_value * 0.0976;                // Рассчитываем показания в процентах 
lcd.setCursor(17, 2);                         // Устанавливаем курсор 
lcd.print(light);                            // Выводим текст 
//ДАТЧИК ТЕМПЕРАТУРЫ И ВЛАЖНОСТЬ НА ДИСПЛЕЙ 
 float h = dht.readHumidity(); //Измеряем влажность 
 float t = dht.readTemperature(); //Измеряем температуру 
 lcd.setCursor(17,0);      
 lcd.print(h, 0);   
 lcd.setCursor(17,1);            
 lcd.print(t, 0);  
 so2 = sol * 0.0976;                // Рассчитываем показания в процентах   
 sol = analogRead(solPin); 
 so2 = map(sol, AirValue, WaterValue, 0, 100); 
 lcd.setCursor(16,3);   
 lcd.print(so2);  
 delay(1500);  
  }
