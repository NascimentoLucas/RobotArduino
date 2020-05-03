class WifiObject
{
  //ATÉ QUE O NÚMERO DE TENTATIVAS EXPIRE (RESULTANDO EM WL_NO_SHIELD) OU QUE UMA CONEXÃO SEJA ESTABELECIDA
  //(RESULTANDO EM WL_CONNECTED)

  int statusLed = LOW; //VARIÁVEL QUE ARMAZENA O ESTADO ATUAL DO LED (LIGADO / DESLIGADO)
  int pinPower;
  WiFiEspClient client;
  inline void sendLine(WiFiEspClient client, char head[], int value)
  {
    //client.print(";");
    //client.print(head);
    client.println(value);
    client.print(";");
  }

  void sendHttpResponse(WiFiEspClient client)
  {
    client.println("HTTP/1.1 200 OK");         //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
    client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
    client.println("");
    client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
    client.println("<html>");          //ABRE A TAG "html"
    client.println("<head>");          //ABRE A TAG "head"
    client.println("<script type=\"text/javascript\" src=\"http://devlucasnascimento.com.br/Arduino/loadHtml.js \"></script>");
    client.println("</head>"); //FECHA A TAG "head"

    //AS LINHAS ABAIXO CRIAM A PÁGINA HTML
    client.println("<body>"); //ABRE A TAG "body"
    client.println("<iframe id=\"contentTest\" style=\"border:none;\">");
    client.println("</iframe>");
    client.println("<p id=\"ip\">");
    client.println("</p>");
    client.println("<hr />");  //TAG HTML QUE CRIA UMA LINHA NA PÁGINA
    client.println("<hr />");  //TAG HTML QUE CRIA UMA LINHA NA PÁGINA
    client.println("</body>"); //FECHA A TAG "body"
    client.println("</html>"); //FECHA A TAG "html"

    delay(1); //INTERVALO DE 1 MILISSEGUNDO
  }

  void sendHttpFeedback(WiFiEspClient client)
  {
    client.println("HTTP/1.1 200 OK");         //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
    client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
    client.println("");
    client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
    client.println("<html>");          //ABRE A TAG "html"
    client.println("<head>");          //ABRE A TAG "head"
    client.println("</head>");         //FECHA A TAG "head"

    //AS LINHAS ABAIXO CRIAM A PÁGINA HTML
    client.println("<body>"); //ABRE A TAG "body"
    client.println("<hr />"); //TAG HTML QUE CRIA UMA LINHA NA PÁGINA
    if (statusLed == 0)
    {
      client.println("<p>Energia Ligada</p>");
    }
    else
    {
      client.println("<p>Energia Desligada</p>");
    }

    client.println("<hr />");  //TAG HTML QUE CRIA UMA LINHA NA PÁGINA
    client.println("</body>"); //FECHA A TAG "body"
    client.println("</html>"); //FECHA A TAG "html"

    delay(1); //INTERVALO DE 1 MILISSEGUNDO
  }

public:
  int status = WL_IDLE_STATUS; //STATUS TEMPORÁRIO ATRIBUÍDO QUANDO O WIFI É INICIALIZADO E PERMANECE ATIVO
  WifiObject(SoftwareSerial Serial1, WiFiEspServer server)
  {
  }

  void update(WiFiEspServer server, RingBuffer buf)
  {
    if (client)
    {             //SE CLIENTE TENTAR SE CONECTAR, FAZ
      buf.init(); //INICIALIZA O BUFFER
      while (client.connected())
      { //ENQUANTO O CLIENTE ESTIVER CONECTADO, FAZ
        if (client.available())
        {                         //SE EXISTIR REQUISIÇÃO DO CLIENTE, FAZ
          char c = client.read(); //LÊ A REQUISIÇÃO DO CLIENTE
          buf.push(c);            //BUFFER ARMAZENA A REQUISIÇÃO

          //IDENTIFICA O FIM DA REQUISIÇÃO HTTP E ENVIA UMA RESPOSTA
          if (buf.endsWith("GET /I"))
          {
            sendHttpResponse(client);
            break;
          }
          if (buf.endsWith("GET /H"))
          {                               //SE O PARÂMETRO DA REQUISIÇÃO VINDO POR GET FOR IGUAL A "H", FAZ
            digitalWrite(pinPower, HIGH); //ACENDE O LED
            statusLed = 1;                //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ ACESO)
            sendHttpFeedback(client);
            Serial.println("GET H");
            break;
          }
          else
          { //SENÃO, FAZ
            if (buf.endsWith("GET /L"))
            {                              //SE O PARÂMETRO DA REQUISIÇÃO VINDO POR GET FOR IGUAL A "L", FAZ
              digitalWrite(pinPower, LOW); //APAGA O LED
              statusLed = 0;               //VARIÁVEL RECEBE VALOR 0(SIGNIFICA QUE O LED ESTÁ APAGADO)
              sendHttpFeedback(client);
              Serial.println("GET L");
              break;
            }
          }
        }
      }
      client.stop(); //FINALIZA A REQUISIÇÃO HTTP E DESCONECTA O CLIENTE
    }
    else
    {
      client = server.available(); //ATENDE AS SOLICITAÇÕES DO CLIENTE
    }
  }

  //MÉTODO DE RESPOSTA A REQUISIÇÃO HTTP DO CLIENTE
};