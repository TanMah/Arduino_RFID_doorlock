
/*
//WITHOUT LED
#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

  // เมื่อถึงส่วนนี้ ตัวแปร strID จะเก็บค่า UID ของแท็กไว้แล้ว
  // สามารถนำไปใช้งานได้เลย เช่น นำไปเข้า IF เพื่อให้หลอด
  // LED ติดสว่าง หรือดับได้
  Serial.print("Tap card key: ");
  Serial.println(strID);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}


//เมื่ออัพโหลดเสร็จแล้ว เปิด Serial Moniter ขึ้นมา ตั้ง Baud rate ไว้ที่ 9600 ลองนำแท็กทั้ง 2 อันมาแตะ จะให้ค่า UID ที่ต่างกันออกมา



//ค่า UID นี้ (หรือ key) จะถูกเก็บไว้ในตัวแปร strID ซึ่งจะใช้งานได้หลังบรรทัดที่ 41 ลงมา ตัวอย่างโค้ดด้านล่างนี้เป็นการประยุกต์นำแท็ก RFID มาควบคุมกับติดดับของหลอด LED
*/
#include<Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

#define GRN_LED 7
#define RED_LED 6

// defining how many rows and columns our keypad have
const byte rows = 4;
const byte columns = 4;

// Keypad pin map
char hexaKeys[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Initializing pins for keypad
byte row_pins[rows] = {0,2,3,4};
byte column_pins[columns] = {A3, A2, A1};
//char initial_password[4] = {'0', '1', '2'};  // Variable to store initial password
//char initial_password = "012*";
//String initial_password = "^def";
char passcode[4];
char validate[4]="1234";
char key_pressed1;
  char key_pressed2;
  char key_pressed3;
  char key_pressed4;
  char key_pressed;
  
  char pass1='1';
  char pass2='2';
  char pass3='4';
  char pass4='5';
  int flag=0;
  int i=0;
  

// Create instance for keypad
Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8
#define GRN_LED 7
#define RED_LED 6
//#define BUZZER 5
int BUZZER=5;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,16,2) for 16x2 LCD.
Servo myservo;  // create servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int val;
MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
    pinMode(GRN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER,OUTPUT);
    myservo.attach(8);  
    lcd.begin();
    lcd.backlight();
    
}

void loop() {
  

    lcd.setCursor(0,0);
    lcd.print("Tap RFID Card");
    
  
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    Serial.println("Door locked");
    
    lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
    lcd.print("Invalid type");
    lcd.setCursor(0, 1); //Set the cursor on the first column and the second row (counting starts at 0!).
    lcd.print("Door locked");
    //return;
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(2000);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    lcd.clear();
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

  Serial.print("Tap card key: ");
  Serial.println(strID);

  
 

if(strID.indexOf("F4:53:9E:22")>=0){
  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RFID Accepted");
      digitalWrite(GRN_LED, HIGH);
      digitalWrite(BUZZER, HIGH);
      delay(500);
      digitalWrite(BUZZER, LOW);
      delay(1000);
      lcd.clear();
      digitalWrite(GRN_LED, LOW);
      
      
      flag=1;      
}

if(flag==1){
   lcd.print("Enter Passcode : ");
   lcd.setCursor(0,1);
   Serial.print("Enter Passcode:\n");
   key_pressed1 = keypad_key.waitForKey();
   passcode[0]=key_pressed1;
   Serial.print(key_pressed1);
   lcd.print(key_pressed1);
   digitalWrite(BUZZER, HIGH);
   delay(250);
   digitalWrite(BUZZER, LOW);
   i++;
   key_pressed2 = keypad_key.waitForKey();
   passcode[1]=key_pressed2;
   Serial.print(key_pressed2);
   lcd.print(key_pressed2);
   digitalWrite(BUZZER, HIGH);
   delay(250);
   digitalWrite(BUZZER, LOW);
   i++;
   key_pressed3 = keypad_key.waitForKey();
   passcode[2]=key_pressed3;
   Serial.print(key_pressed3);
   lcd.print(key_pressed3);
   digitalWrite(BUZZER, HIGH);
   delay(250);
   digitalWrite(BUZZER, LOW);
   i++;
   key_pressed4 = keypad_key.waitForKey();
   passcode[3]=key_pressed4;
   Serial.print(key_pressed4);
   lcd.print(key_pressed4);
   digitalWrite(BUZZER, HIGH);
   delay(250);
   digitalWrite(BUZZER, LOW);
   i++;
   
        
           
}

if(i%4==0){
    delay(500);
    lcd.clear();
    if(!strncmp(validate,passcode,4)){

  Serial.println("\nDoor Unlocked");
  flag=1;
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("Door Unlocked");
  digitalWrite(GRN_LED, HIGH);
  digitalWrite(BUZZER, HIGH);
  
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  //sdelay(15);  
  
  delay(500);
  digitalWrite(GRN_LED, LOW);
  digitalWrite(BUZZER, LOW);
  delay(1000);
  lcd.clear();
  //digitalWrite(RED_LED, LOW);
  }
  else{
    //digitalWrite(GRN_LED, LOW);
    flag=1;
    lcd.print("Door Locked");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
  
    
    delay(2000);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
  
  }

  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

}





  
