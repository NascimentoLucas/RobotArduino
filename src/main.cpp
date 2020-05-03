#include "WiFiEsp.h"        //INCLUSÃO DA BIBLIOTECA
#include "SoftwareSerial.h" //INCLUSÃO DA BIBLIOTECA
#include "WifiClass.h"
#include <Arduino.h>

SoftwareSerial bluetooth(2, 3); //PINOS QUE EMULAM A SERIAL, ONDE
//O PINO 2 É O RX E O PINO 3 É O TX

SoftwareSerial wifiSerial(6, 7);
WiFiEspServer server(80); //CONEXÃO REALIZADA NA PORTA 80
WifiObject wf(wifiSerial, server);

void setup()
{
  Serial.begin(9600); //INICIALIZA A SERIAL

  String ssid = "";
  String password = "";

  bluetooth.begin(9600); //INICIALIZA A SERIAL DO BLUETOOTH
  bluetooth.print("$");  //IMPRIME O CARACTERE
  bluetooth.print("$");  //IMPRIME O CARACTERE
  bluetooth.print("$");  //IMPRIME O CARACTERE
  delay(100);            //INTERVALO DE 100 MILISSEGUNDOS

  boolean free = false;
  boolean hasName = false;

  Serial.println("Please input SSID: ");
  bluetooth.println("Please input SSID: ");

  int dadoBluetooth = 0; //VARIÁVEL QUE ARMAZENA O VALOR ENVIADO PELO BLUETOOTH
  do
  {
    while (bluetooth.available())
    {
      dadoBluetooth = bluetooth.read();
      char c = dadoBluetooth;
      if (c == '\n')
      {
        if (!hasName)
        {
          bluetooth.print("SSID: ");
          bluetooth.println(ssid);
          hasName = true;
          bluetooth.println("Please input password");
          Serial.println("ssid");
          Serial.println(ssid);
          continue;
        }
        else
        {
          bluetooth.println(password);
          free = true;
          Serial.println("password");
          bluetooth.println("Connecting");
          Serial.println(password);
          break;
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

  bluetooth.print("Start Connect");
  Serial.print("Start Connect");
  Serial.println(ssid);
  Serial.println(password);

  char ssidChar[ssid.length() + 1];
  ssid.toCharArray(ssidChar, ssid.length() + 1);

  char passwordChar[password.length() + 1];
  password.toCharArray(passwordChar, password.length() + 1);

  wifiSerial.begin(9600);
  WiFi.init(&wifiSerial); //INICIALIZA A COMUNICAÇÃO SERIAL COM O ESP8266
  if (WiFi.status() == WL_NO_SHIELD)
  {
    while (true)
      ;
  }
  while (wf.status != WL_CONNECTED)
  {
    wf.status = WiFi.begin(ssidChar, passwordChar);
  }
  Serial.println("Start Server");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
}