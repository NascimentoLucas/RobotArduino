#include <Arduino.h>
#include "SoftwareSerial.h"

SoftwareSerial bluetooth(2, 3);

int dadoBluetooth = 0;

void setup()
{
  Serial.begin(9600);    //INICIALIZA A SERIAL
  bluetooth.begin(9600); //INICIALIZA A SERIAL DO BLUETOOTH
  bluetooth.print("$");  //IMPRIME O CARACTERE
  bluetooth.print("$");  //IMPRIME O CARACTERE
  bluetooth.print("$");  //IMPRIME O CARACTERE
  delay(100);            //INTERVALO DE 100 MILISSEGUNDOS

    Serial.println("Start");
  bluetooth.println("Start");
}

void loop()
{
  while (bluetooth.available())
  {
    dadoBluetooth = bluetooth.read();
    char c = dadoBluetooth;
    Serial.print(c);
  }
}