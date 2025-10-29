 #include "HX711.h"
#include <LiquidCrystal_I2C.h>
#include <HX711_ADC.h> // need to install 

LiquidCrystal_I2C lcd(0x27,20,2);

HX711_ADC LoadCell(8, 9); // parameters: dt pin 6, sck pin 7;

// HX711 circuit wiring
//const int LOADCELL_DOUT_PIN = 8;
//const int LOADCELL_SCK_PIN = 9;
//HX711 scale;
uint8_t nb;
#define BUTTON_PIN 2
volatile int averageValue;
volatile int state=0;

void test(){ 
  
  //if(state==0){
  //scale.set_scale(36.059);  
  //scale.tare(2);
   LoadCell.begin(); // start connection to HX711
  
  LoadCell.setCalFactor(1000.0); // calibration factor for load 
  
 // state=1;}
  
  lcd.clear();
 // Calculate and store the value
   LoadCell.update();
   float i = LoadCell.getData(); // get output value
   averageValue = round(i / 8);
   if(averageValue <0){
    lcd.setCursor(0,0);//first line 
     Serial.println(" measured weight");
     Serial.println("");
  lcd.print("Measured Weight");
  lcd.setCursor(0,1);//second line 
  lcd.print(0);
  lcd.print("\t| nb:\t");
  lcd.print(0); 
   }else{
  // Display the results
      Serial.println("  weight");
      Serial.println(i / 1000, 1);
  lcd.setCursor(0,0);//first line 
  lcd.print("Measured Weight");
  lcd.setCursor(0,1);//second line 
  lcd.print(i / 1000, 1);
  lcd.print( " |nb: ");
  lcd.print(averageValue);
   }
 


}
void setup() {
  LoadCell.begin(); // start connection to HX711
  LoadCell.start(2000); // load cells gets 2000ms of time to stabilize
  LoadCell.setCalFactor(1000.0); // calibration factor for load 
  Serial.begin(9600);
   lcd.init();                      // initialize the lcd 
    lcd.backlight();
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), test, HIGH);
 
   pinMode(BUTTON_PIN,INPUT_PULLUP);
//scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
   Serial.println("weight");
   Serial.println("Measurement");
lcd.print(" Weight ");
lcd.setCursor(0,1);
lcd.print(" Measurement ");;

  // put your setup code here, to run once:
  

  
  
 
}

void loop() {

}
