#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3405vKSm"
#define BLYNK_DEVICE_NAME "weather staion"
 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//------------ LCD  --------------------
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2); // scl 22 - sda 21

//------------ end ---------------------

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "10dzkGl_AjlDy5CqhxIOe5td8bTCVR53";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iPhone";
char pass[] = "100200800900";
 
int gas_sensor_pin = A0 ; // D4
int Gas_Value=0;
int v;
BlynkTimer timer;
 
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
 
  Blynk.virtualWrite(V0, Gas_Value);
}


void Gas_sensor() {

  v=analogRead(gas_sensor_pin);
     Gas_Value = map(v, 0 , 4095, 0.5, 1000);
  Serial.print("air_quality_value:");
  Serial.print(Gas_Value);
  Serial.println(" ppm"); 
  lcd.setCursor(0, 0);lcd.print("Gas:");
  lcd.setCursor(5, 0);lcd.print(Gas_Value);
  lcd.setCursor(8, 0);lcd.print(" ppm");
  delay(500);
  lcd.clear();
 

}



 
void setup()
{
  // Debug console
  Serial.begin(9600);
   //------- LCD ----- 
  lcd.begin();
  lcd.backlight();
  lcd.print("Gas system init.");
   delay(3000);
   lcd.clear();
//----- end -------

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  Gas_sensor();
  //------------------------
  Blynk.run();
  timer.run();

}
