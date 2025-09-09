# Arduino LDR & RTC DS3231

This repository contains sample Arduino codes for:
- Reading analog values from an LDR (Light Dependent Resistor).
- Reading real-time clock data (time and date) from the RTC DS3231 module.

## 📦 Requirements
- Arduino IDE (latest version recommended)
- Arduino board (Uno, Mega, Nano, ESP32, etc.)
- RTC DS3231 module
- LDR (Light Dependent Resistor)
- 10kΩ resistor (for voltage divider with LDR)
- Jumper wires & breadboard

## 🔌 Wiring

### LDR
LDR ---- A0 (Arduino)
LDR ---- VCC (5V or 3.3V depending on board)
10kΩ resistor between LDR and GND

### RTC DS3231
VCC → 5V (or 3.3V on ESP32/ESP8266)
GND → GND
SDA → A4 (Arduino Uno) / D21 (ESP32)
SCL → A5 (Arduino Uno) / D22 (ESP32)

## 📜 Example Codes

### 1. Read LDR Value
```cpp
int readLDR(int pin) {
  return analogRead(pin);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = readLDR(A0);
  Serial.println(value);
  delay(500);
}
```

### 2. Read RTC DS3231 Time
```cpp
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void setup () {
  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
}

void loop () {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  delay(1000);
}
```

### 🚀 How to Use

Clone this repository:

git clone https://github.com/your-username/arduino-ldr-rtc-ds3231.git

Open the .ino file in Arduino IDE.

Select the correct board and COM port.

Upload to your Arduino/ESP32 board.

Open Serial Monitor to see results.
