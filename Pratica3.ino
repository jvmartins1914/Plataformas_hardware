#include <FS.h>
#include <SPIFFS.h>

const int pinoBotao = 25; 
const int pinoLed = 26;   

bool estadoLed = false;   // Estado inicial do LED
bool ultimoEstadoBotao = HIGH;  // Estado anterior do botão
bool estadoAtualBotao;      // Estado atual do botão

void setup() {
  Serial.begin(9600);

  pinMode(pinoBotao, INPUT);
  pinMode(pinoLed, OUTPUT);

  // Inicializa o sistema de arquivos SPIFFS
  if (SPIFFS.begin()) {
    // Verifica se o arquivo com o estado do LED existe
    if (SPIFFS.exists("/estadoLed.txt")) {
      // Se existe, abre o arquivo em modo de leitura
      File arquivo = SPIFFS.open("/estadoLed.txt", "r");
      Serial.println("Lendo arquivo!");
      if (arquivo) {
        Serial.println("Lido!");
        // Lê o conteúdo do arquivo até encontrar um caractere de nova linha e converte para inteiro
        estadoLed = arquivo.readStringUntil('\n').toInt();
        arquivo.close(); // Fecha o arquivo
      }
    }
  }

  digitalWrite(pinoLed, estadoLed); // Define o estado inicial do LED
}

void loop() {
  
  estadoAtualBotao = digitalRead(pinoBotao); // Lê o estado atual do botão

  if (estadoAtualBotao == LOW && ultimoEstadoBotao == HIGH) {
    // Se o botão foi pressionado e estava solto no ciclo anterior
    estadoLed = !estadoLed; // Inverte o estado do LED
    digitalWrite(pinoLed, estadoLed); // Atualiza o estado do LED

    // Salva o estado atual do LED no arquivo
    File arquivo = SPIFFS.open("/estadoLed.txt", "w");
    if (arquivo) {
      Serial.println("Escrevendo no arquivo");
      arquivo.print(estadoLed);
      arquivo.close(); // Fecha o arquivo
    }
  }

  ultimoEstadoBotao = estadoAtualBotao; // Atualiza o estado anterior do botão para o atual
}
