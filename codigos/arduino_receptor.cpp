//Carrega a biblioteca SoftwareSerial
#include <SoftwareSerial.h> 

//Define os terminais RX e TX para comunicação com HC-06
SoftwareSerial mySerial(10, 11); //Define os terminais RX e TX para comunicação com HC-06
String command = ""; // Armazena a resposta do HC-06

void setup()
{
  // Abre as comunicações seriais e aguarda a abertura da porta:
  Serial.begin(115200);
  pinMode(7,OUTPUT);
  //Configura a porta para comunicação do dispositivo bluetooth:
  mySerial.begin(9600);
}

void loop()
{
  // Lê a saída do dispositivo, se disponível:
  if (mySerial.available())
  {
    while (mySerial.available())
    { // Enquanto houver mais para ser lido, o codigo continua lendo:
      command += (char)mySerial.read();
    }
      //Faz o print no monitor seiral das informações recebida pelo dispositivo bluetooth:  
    Serial.println(command);
    
     //Se o codigo recebido pelo HC-06 for "1" o pino digital 7 muda o estado digital para Alto:
    if (command == "1") {
  
      digitalWrite(7, HIGH);

    } else {
     //Se o codigo recebido pelo HC-06 for "0" o pino digital 7 muda o estado digital para Baixo;
      digitalWrite(7, LOW);
    }



    command = ""; // Interrompe a Repetição 
  }


} //Fim do Loop