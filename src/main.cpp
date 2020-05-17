//https://blogmasterwalkershop.com.br/arduino/como-usar-com-arduino-modulo-bluetooth-hc-05-hc-06/
#include <Arduino.h>
#include "SoftwareSerial.h"
#include "Giro.h"

SoftwareSerial giro(6, 7);
SoftwareSerial bluetooth(2, 3);

#define LED 13

int dadoBluetooth = 0;
String info;
bool data = false;

GiroObject go(0x68);

void setup()
{
  bluetooth.begin(9600); //INICIALIZA A SERIAL DO BLUETOOTH
  delay(100);            //INTERVALO DE 100 MILISSEGUNDOS

  pinMode(LED, OUTPUT);

  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);

  //Inicializa o MPU-6050
  Wire.write(0);
  Wire.endTransmission(true);

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

    go.GiroUpdate();
    info = "";
    info = info + "lastAcX=" + go.lastAcX + ";";
    info = info + "lastAcY=" + go.lastAcY + ";";
    info = info + "lastAcZ=" + go.lastAcZ + ";";
    info = info + "lastGyX=" + go.lastGyX + ";";
    info = info + "lastGyY=" + go.lastGyY + ";";
    info = info + "lastGyZ=" + go.lastGyZ + ";";

    data = false;
    bluetooth.println(info);
  }
}
