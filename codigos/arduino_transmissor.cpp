//Carrega a biblioteca SoftwareSerial 
#include <SoftwareSerial.h>  

 //Define os terminais RX e TX para comunicação com HC-05 (comunicador bluetooth)
SoftwareSerial mySerial(0,1); 

void setup()
{  
  //Configura porta digital 7 como Entrada
  pinMode(7,INPUT);
  //Inicializa a serial nas portas 10 e 11
  mySerial.begin(9600);
}
 
void loop()
{
  //Caso o estado digital do pino digital 7 for Alto, Será enviado pelo comunicador bluetooth o valor "1" em Binário
  if(digitalRead(7) == HIGH){
  mySerial.print(1,BIN);
  delay(3000);
  }
  //Caso o estado digital do pino digital 7 for Baixo, Será enviado pelo comunicador bluetooth o valor "0" em Binário
  if(digitalRead(7) == LOW){
  mySerial.print(0,BIN);
  delay(3000);
    }
  }//Fim do Loop