#include <SoftwareSerial.h> //INCLUSÃO DE BIBLIOTECA
#include <Arduino.h>

#define SIZE 9

const int pinoRX = 2;    //PINO DIGITAL 2 (RX)
const int pinoTX = 3;    //PINO DIGITAL 3 (TX)
const int pinoLed = 13;  //PINO DIGITAL UTILIZADO PELO LED
int dadoBluetooth = 0;   //VARIÁVEL QUE ARMAZENA O VALOR ENVIADO PELO BLUETOOTH
boolean loopLED = false; //VARIÁVEL BOOLEANA QUE FAZ O CONTROLE DE ATIVAÇÃO DO LOOP DO LED

SoftwareSerial bluetooth(pinoRX, pinoTX); //PINOS QUE EMULAM A SERIAL, ONDE
//O PINO 2 É O RX E O PINO 3 É O TX

void setup()
{
  Serial.begin(9600);    //INICIALIZA A SERIAL
  bluetooth.begin(9600); //INICIALIZA A SERIAL DO BLUETOOTH
  bluetooth.print("$");  //IMPRIME O CARACTERE
  bluetooth.print("$");  //IMPRIME O CARACTERE
  bluetooth.print("$");  //IMPRIME O CARACTERE
  delay(100);            //INTERVALO DE 100 MILISSEGUNDOS

  String ssid = "";
  String password = "";
  boolean free = false;
  boolean hasName = false;

  Serial.println("Please input SSID: ");
  bluetooth.println("Please input SSID: ");

  do
  {

    while (bluetooth.available())
    {
      dadoBluetooth = bluetooth.read();
      char c = dadoBluetooth;
      Serial.print(c);
      if (c == '\n')
      {
        if (!hasName)
        {
          bluetooth.print("SSID: ");
          bluetooth.println(ssid);
          hasName = true;
          bluetooth.println("Please input password");
          Serial.println(ssid);
          Serial.println("\n");
        }
        else
        {
          bluetooth.println(password);
          free = true;
          bluetooth.println("Connecting");
          Serial.println(password);
        }
      }

      if (!hasName)
      {
        ssid += c;
      }
      else
      {
        password += c;
      }
    }

  } while (!free);

  bluetooth.print("Start");
}

void loop()
{
}