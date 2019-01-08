#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"



char dias[7][19] = {"Domingo", "Segunda-Feira", "Terça-Feira", "Quarta-Feira", "Quinta-Feira", "Sexta-Feira", "Sabado"};


#define ldr A7
#define lm35 0
#define rele_pin 5

///Amostras//
float vetLux[10] = {0,0,0,0,0,0,0,0,0};

const int corte = 10000;
unsigned long deltaTemp = millis();
boolean  limpa;
///Lm35
float temperatura;
int lm35_let;
unsigned long  tempo = 5000;//um minuto
///lux variaveis
float const ADC_tes = 0.004882812;
///Funçoes auciliares///
void aciona();
int leitura_dc();
float lm35_dz();
float  lux(int ldr_val);
///Matriz//
void construi();
void amostras();
////--------------- 
void rele();
void rele_ap();

///Tempo//
DateTime utc;

byte apaga[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b11111,
  0b01110,
  0b00100,
  0b00100,
  0b00000
};

byte luz[8] = {
  0b10001,
  0b01010,
  0b01110,
  0b11111,
  0b01110,
  0b10101,
  0b00100,
  0b00000
};

void iniciarRTC();
// Set the LCD address to 0x27 for a 16 chars and 2 line display
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup()
{
 
	// initialize the LCD
	lcd.begin();
  Serial.begin(57600);
  pinMode(rele_pin,OUTPUT);
  lcd.createChar(0,apaga);
  lcd.createChar(1,luz);
///----------------------------------------------
	// Turn on the blacklight and print a message.
	lcd.backlight();
  lcd.setCursor(4,0);
  lcd.blink();
  iniciarRTC();

  
}


void loop()
{
/// LM35 //
//serial.println(lm35_dz());
//Serial.println(lm35_dz());

//Leitura de Dados LDR e ds 1037/// 
aciona(); 
amostras();
construi(); 
  
}


void construi(){
  Serial.print("  Amostras:[");
  for(int i=0;i<10;i++){
    Serial.print(int(vetLux[i]));Serial.print(",");  
}

Serial.print("] Horas:");Serial.print(utc.hour(),DEC);
Serial.print(":");Serial.print(utc.minute(),DEC);
Serial.print(":");Serial.println(utc.second(),DEC);

};

unsigned long delta = millis();

void amostras(){
  int i=0;
  if((millis() - delta) > 5000){
    delta  =  millis();
    for(i=0;i<10;i++){
      vetLux[i] = vetLux[i+1];
      vetLux[9]  = int(lux(leitura_dc())); 
      

    }
     
  
}
   

};

void iniciarRTC(){ 
 rtc.begin();  ///Iniciar rtc 
 rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));///Horas get
 
 utc = rtc.now(); 
 DateTime future (utc + TimeSpan(7,12,30,6));

 lcd.setCursor(0,0);
 lcd.print("Dia:");
 lcd.print(dias[utc.dayOfTheWeek()]);//Selecionar Um dia da semana 
 lcd.setCursor(8,1);
 lcd.write(1);
 delay(5000);
 
 /////Quando não Copilar o programa////
 while (!Serial); // for Leonardo/Micro/Zero
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }


  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
     //rtc.adjust(DateTime(2018, 12, 18, 6, 8, 0));
     //ano / mes /dia/hora minuto e segundo
  }
  
  //Serial.print(dias[utc.dayOfTheWeek()]);
  lcd.print(utc.hour(),DEC);lcd.print(":");
  lcd.print(utc.minute(),DEC);lcd.print(":");
  lcd.print(utc.second(),DEC);

  //lcd.print(future.hour(),DEC);lcd.print(":");
  //lcd.print(future.minute(),DEC);lcd.print(":");
  //lcd.print(future.second(),DEC);

  

}


int  leitura_dc(){
 while(1){
  int dc = analogRead(ldr);
  int leitura = map (dc,0,1023,0,1023); 
  return leitura;
 }
 
}

float lm35_dz(){
lm35_let = analogRead(lm35);
temperatura = lm35_let * 0.00488;
temperatura = temperatura  * 100;
return  temperatura;


}

float  lux(int ldr_val){
float lux = (250.000000/(ADC_tes*ldr_val))-50.000000;
return lux;
}

void rele(){
 // digitalWrite(rele_pin,LOW);
  digitalWrite(rele_pin,HIGH);
   
}

void rele_ap(){
 // digitalWrite(rele_pin,LOW);
  digitalWrite(rele_pin,LOW);
   
}
boolean trava;

void aciona(){
DateTime utc = rtc.now(); 

if(lux(leitura_dc()) >= 7.0){
 if (millis() - deltaTemp < tempo){
  lcd.print("Lux:");
  lcd.print(lux(leitura_dc()));
  lcd.setCursor(0,1);

  lcd.print("Data:");
  lcd.print(utc.year(),DEC);lcd.print("/");
  lcd.print(utc.month(),DEC);lcd.print("/");
  lcd.println(utc.day(),DEC);
  rele_ap();
  trava = true;

 }


 else{
   deltaTemp = millis();  
   lcd.clear();
   lcd.noBlink();
}

  }

else{
   trava = false;
   lcd.noBlink();
   lcd.clear();
   lcd.setCursor(2,1);
   lcd.print("Acenda a Luz");
   lcd.setCursor(8,0);
   lcd.write(0);
   do{  
    rele();
   }while (lux(leitura_dc()) <= 7.0 && trava == true);
   delay(tempo);
   
 
  }


  
}







