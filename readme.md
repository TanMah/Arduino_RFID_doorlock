# 🔐 Arduino RFID + Keypad Door Lock System

This project combines RFID authentication and keypad PIN entry to control a servo-powered door lock, with status displayed on an I2C LCD and feedback through LEDs and a buzzer.

## ✅ Features

- Dual authentication: RFID tag + 4-digit PIN
- LCD instructions and feedback
- Servo motor for door locking/unlocking
- Buzzer and LED indicators for access status
- Basic access control logic (hardcoded credentials)

## 🧰 Components Used

- Arduino Uno
- MFRC522 RFID module
- 4x4 matrix keypad
- SG90/MG90S servo motor
- 16x2 I2C LCD display
- Red & green LEDs
- Passive buzzer
- RFID tags/cards

## 🔌 Key Connections (Pin Mapping)
Component	Arduino Pin
RFID SDA	10
RFID RST	9
Servo	8
Green LED	7
Red LED	6
Buzzer	5
Keypad Rows	0, 2, 3, 4
Keypad Cols	A3, A2, A1
Potentiometer	A0
