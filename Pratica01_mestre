#include <SoftwareSerial.h>

SoftwareSerial ArduinoSlave(10, 11);

const int sensorLuminosidadePin = A0;
const int botaoPin = 2;

void setup() {
  ArduinoSlave.begin(9600);
  pinMode(botaoPin, INPUT_PULLUP);
}

void loop() {
  int valorLuminosidade = analogRead(sensorLuminosidadePin);
  int estadoBotao = digitalRead(botaoPin);

  ArduinoSlave.print("Luminosidade:");
  ArduinoSlave.print(valorLuminosidade);
  ArduinoSlave.print(",Botao:");
  ArduinoSlave.println(estadoBotao);

  delay(1000);  
}
