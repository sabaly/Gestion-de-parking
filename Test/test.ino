/*
  Projet de fin d'année : Mise en place d'un parking connecté avec une application de gestion

  Aminata Diallo
  Thierno Mamoudou Sabaly

  Voici le programme arduino de ce projet. 
*/

#include <SPI.h>
#include <LiquidCrystal.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST 5
#define SS 53
#define contrast 9
#define brightness 10

MFRC522 module_rfid(SS, RST);

//pin leds
const byte LedRouge = 40;
const byte LedVerte = 38;

//pins LCD
LiquidCrystal lcd(12, 11, 30, 32, 34, 36);

//variables servomoteur
Servo myservo;
int pos = 0;

//variable lecture série
char serie = 'r';
//variable etat scanner
int scanner = 0;
//variable etat moteur
int actionner = 0;
void setup() {
  //Leds
  pinMode(LedRouge, OUTPUT);
  pinMode(LedVerte, OUTPUT);
  //LCD
  InitialiseLCD();
  //RFID
  InitialiseRFID();
  //servo
  myservo.attach(28);
}

void loop() {
  //Affichage du message d'attente
  AttenteLCD();

  if(Serial.available()){
    //lecture du port sérial
    serie = Serial.read();

    if(serie == 'a'){ //correspond lancement de la RFID
      scanner = 1;
      actionner = 0;
    }else if(serie == 'b'){
      scanner = 0;
      actionner = 1;
    }
  }
 String iden = "";
  if(scanner == 1){
    if (! module_rfid.PICC_IsNewCardPresent()) {
      return;
    }

      // Select one of the cards
    if (! module_rfid.PICC_ReadCardSerial()) {
      return;
    }  
    iden = Extract_Stock_Info();
    Serial.println(iden);
  }

  if(actionner == 1){
    for(pos=0; pos < 90; pos += 30){
        myservo.write(pos);
        delay(150);
      }
      delay(1000);
      for (int pos=90; pos >= 0; pos -= 20) {
        myservo.write(pos);              
        delay(150);                      
      }
      Serial.println("Moteur actionne");
  }
}

void InitialiseLCD(){ 
  lcd.begin(16, 2);
  pinMode(contrast, OUTPUT);
  pinMode(brightness, OUTPUT);
  digitalWrite(contrast, LOW);
  analogWrite(brightness, 255);
  lcd.setCursor(0,0);
  lcd.print("Dispositif");
  lcd.setCursor(0,1);
  lcd.print("d'idenification");
  delay(2000);
  lcd.clear();
}

void InitialiseRFID(){
  Serial.begin(9600);
  while(!Serial);
  SPI.begin();
  module_rfid.PCD_Init();
  module_rfid.PCD_DumpVersionToSerial();
}


void AttenteLCD(){
  lcd.setCursor(0,0);
  lcd.print("Scanner votre");
  lcd.setCursor(0,1);
  lcd.print("carte ou badge...");
}

String Extract_Stock_Info(){
  String uid="";
  for(byte i=0; i<module_rfid.uid.size; i++){
    uid.concat(String(module_rfid.uid.uidByte[i] < 0x10 ? " 0 " : " "));
    uid.concat(String(module_rfid.uid.uidByte[i], HEX));  
  }

  uid.toUpperCase();
  
  return uid;
}

void MessageLCD_Led(boolean b){
  if(b){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Acces autorise");
    digitalWrite(LedVerte, HIGH);
  }else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Acces refuse");
    digitalWrite(LedRouge, HIGH);
  }
}

void ActionnerMoteur(){
    for (int pos = 110; pos >= 30; pos -= 20) {
        myservo.write(pos);              
        delay(150);                      
      }
}

void RemetMoteur(){
    for(int pos = 30; pos <= 110; pos += 20) {
        myservo.write(pos);              
        delay(150);                      
     }

}
