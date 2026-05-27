
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLNbp-svm0"
#define BLYNK_DEVICE_NAME "Smart City"

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT

#include "BlynkEdgent.h"

#define IR 36
#define LDR 39
#define LED1 21
#define LED2 23
#define LED3 2
#define LED4 22

int pinValue1;
int pinValue;
void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(LDR, INPUT);
  pinMode(IR, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  BlynkEdgent.begin();
}

void loop() {
  LDR_sensor();
  BlynkEdgent.run();
  
}

BLYNK_WRITE(V0)
{
  pinValue = param.asInt();
    
    //analogWrite(LED1, pinValue);
    //analogWrite(LED2, pinValue);
    //analogWrite(LED3, pinValue);
    //analogWrite(LED4, pinValue);
}

BLYNK_WRITE(V3)
{
  pinValue1 = param.asInt();
}

void LED_on()
{
  //int pinValue;
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
}

void LED_off()
{
  //int pinValue;
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void LDR_sensor()
{
  String req;
  Serial.println("In LDR Sensor Section");
  
  int LDRVALUE = analogRead(LDR);
  int IRVALUE   = digitalRead(IR) ;

  Serial.print("LDR Sensor Reading = ");
  Serial.println(LDRVALUE);
  Blynk.virtualWrite(V1, LDRVALUE);
  delay(1000);
  
  if(pinValue1==1)
  {
    digitalWrite(LED1, pinValue);
    digitalWrite(LED2, pinValue);
    digitalWrite(LED3, pinValue);
    digitalWrite(LED4, pinValue);
    //analogWrite(LED1, pinValue);
    //analogWrite(LED2, pinValue);
    //analogWrite(LED3, pinValue);
    //analogWrite(LED4, pinValue);
  }
  else
  {
    if (LDRVALUE > 2000)
    {
      Serial.println("It's Dark Outside; Lights status: ON");
      LED_on();
      delay (10000);
      LED_off();
      
      if(IRVALUE==HIGH)
      {
        Serial.println("In If Part");
        while(1)
        {
          Serial.println("In While Loop");
          Serial.print("IR Sensor Reading = ");
          Serial.println(IRVALUE);
          Blynk.virtualWrite(V2, IRVALUE);
          delay(1000);
          Serial.println("Vehical is Not Detected; Light status: OFF");
          LED_off();
          break;
        }
      }
      else
      {
        Serial.println("In Else Part");
        while(1)
        {
          Serial.println("In While Loop");
          Serial.print("IR Sensor Reading = ");
          Serial.println(IRVALUE);
          Blynk.virtualWrite(V2, IRVALUE);
          delay(1000);
          Serial.println("Vehical is Detected; Light status: ON");
          LED_on();
          delay(10000);
          break;
        }
      }
    }
      else
    {
      Serial.println("It's Bright Outside; Light ststus: OFF");
      LED_off();     // turning off all the lights
     }
  }
}
