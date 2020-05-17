//https://blogmasterwalkershop.com.br/arduino/como-usar-com-arduino-modulo-bluetooth-hc-05-hc-06/
#include <Arduino.h>
#include "SoftwareSerial.h"
#include "Giro.h"

SoftwareSerial bluetooth(2, 3);

#define LED 13

int dadoBluetooth = 0;

bool data = false;

GiroObject go(0x68);

void setup()
{
  Serial.begin(9600);    //INICIALIZA A SERIAL
  bluetooth.begin(9600); //INICIALIZA A SERIAL DO BLUETOOTH
  delay(100);            //INTERVALO DE 100 MILISSEGUNDOS

  pinMode(LED, OUTPUT);

  Serial.println("Start");
  bluetooth.println("Start");
}

void loop()
{
  while (bluetooth.available())
  {
    dadoBluetooth = bluetooth.read();

    if (dadoBluetooth == 'O')
    {
      data = true;
    }
    else if (dadoBluetooth == 'R')
    {
      data = false;
    }
    else if (dadoBluetooth == 'H')
    {
      digitalWrite(LED, HIGH);
      bluetooth.println("Turn On");
    }
    else if (dadoBluetooth == 'L')
    {
      digitalWrite(LED, LOW);
      bluetooth.println("Turn Off");
    }
  }

  if (data)
  {
    data = false;
    String s = "";
    s = s + "lastAcX=" + go.lastAcX + ";";
    s = s + "lastAcY=" + go.lastAcY + ";";
    s = s + "lastAcZ=" + go.lastAcZ + ";";
    s = s + "lastGyX=" + go.lastGyX + ";";
    s = s + "lastGyY=" + go.lastGyY + ";";
    s = s + "lastGyZ=" + go.lastGyZ + ";";

    bluetooth.println(s);
  }
}
