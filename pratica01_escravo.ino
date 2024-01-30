#include <SoftwareSerial.h>

SoftwareSerial ArduinoMaster(10, 11); 

const int ledPin = 9;

void setup() {
  ArduinoMaster.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (ArduinoMaster.available() > 0) {
    String dadosRecebidos = ArduinoMaster.readStringUntil('\n');
    int valorLuminosidade = dadosRecebidos.substring(dadosRecebidos.indexOf(':') + 1, dadosRecebidos.indexOf(',')).toInt();
    int estadoBotao = dadosRecebidos.substring(dadosRecebidos.lastIndexOf(':') + 1).toInt();

    if (estadoBotao == HIGH) {
  
      analogWrite(ledPin, 255);
    } else {
 
      analogWrite(ledPin, map(valorLuminosidade, 0, 1023, 0, 255));


      if (valorLuminosidade < 20) {
        Serial.println("Baixa luminosidade!");
      }
    }
  }
}
