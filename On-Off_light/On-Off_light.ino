#include <Wire.h>
#include <DS3231.h>

const int ledPin = 8;  
const int ldrPin = A3;  

int LDRvalue = 500;

 DS3231 clk;
 
 int format = 24;

//ตั้งเวลาตอนที่ Upload code
 int hours = 0; //ชั่วโมง
 int minutes = 0; //นาที
 int seconds =0; //วินาที


 String time_period = "";
 
 bool h12Flag;
 bool pmFlag;

 bool turn_off_light;
 int start_time = 23; 
 int end_time = 3;
 

 void RTC_setup()
 {  

    Serial.println("-------------------------------------------------------------");
    Serial.print("The RTC is set to : ");
    Serial.print(hours);
    Serial.print(" : ");
    Serial.print(minutes);
    Serial.print(" : ");
    Serial.print(seconds);

    clk.setHour(hours);
    clk.setMinute(minutes);
    clk.setSecond(seconds);
    if (format==12)
      clk.setClockMode(true);
    else
      clk.setClockMode(false);   
    delay(1000);
    Serial.println("RTC has be set with new time.");
    Serial.println("-------------------------------------------------------------");
    Serial.println("The DS3231 time is : ");
 }

 void RTC_Conditioncheck()
 {
    /*
     * This block displays the time in the serial monitor.
     */
    delay(1000);
    
    hours   = clk.getHour(h12Flag,pmFlag);
    minutes = clk.getMinute();
    seconds = clk.getSecond();

    // Print Hours
    if(hours<10)
      Serial.print(" 0");
    else
      Serial.print(" ");
    Serial.print(hours);
    Serial.print(" : ");

    // Print Minutes
    if(minutes<10)
      Serial.print("0");
    Serial.print(minutes);
    Serial.print(" : ");

    // Print Seconds
    if(seconds<10)
      Serial.print("0");
    Serial.print(seconds);

    if ((hours > start_time) or (hours < end_time) ){
        digitalWrite(ledPin, LOW);
    }else{
        openLight(LDRvalue, ldrPin, ledPin);
    }
}

int readLDR(int pin) {
  int value = analogRead(pin);   // Read analog value (0 - 1023 on Arduino UNO)
  return value;
}

void openLight(int value, int LDRpin, int LEDPin) {
  if(readLDR(LDRpin) > value){
  	digitalWrite(ledPin, HIGH);
  } else if(readLDR(LDRpin) < value) {
  	digitalWrite(ledPin, LOW);
  }
}

 void setup()
 {  
    //Set the Baud Rate
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);  
    pinMode(ldrPin, INPUT); 
    RTC_setup();
    
 }

 void loop()
 {
    RTC_Conditioncheck();
 }
