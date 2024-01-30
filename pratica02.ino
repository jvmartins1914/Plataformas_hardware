//Inclui as bibliotecas do SPI e do RC522
#include <SPI.h>
#include <MFRC522.h>
//Definição dos pinos de conexão do projeto
#define PINO_SS 10
#define PINO_RST 9
#define ledRed 5
#define ledgreen 6
int erro = 0;
//F3 7A EA 11
//Cria o item para configurar o módulo RC522
MFRC522 mfrc522(PINO_SS, PINO_RST);
void setup() {
 pinMode(7, OUTPUT);
 pinMode(ledRed, OUTPUT);
 pinMode(ledgreen, OUTPUT);
 Serial.begin(9600); // Inicializa a serial
 SPI.begin();// Inicializa a comunicação SPI
 mfrc522.PCD_Init(); // Inicializa o módulo MFRC522
 Serial.println("Sistema Inicializado: Aproxime o token");
}
void loop() {
  digitalWrite(ledRed, HIGH);
   if (!mfrc522.PICC_IsNewCardPresent()) return;// Aguarda a
//aproximação do token
 if (!mfrc522.PICC_ReadCardSerial()) return; // Seleciona qual token
//vai ser utilizado
 Serial.print("UID da tag:"); // Mostra UID do token na serial
 String conteudo= ""; //Cria uma variável vazia, do tipo string
 byte letra;
 for (byte i = 0; i < mfrc522.uid.size; i++) {
 if(mfrc522.uid.uidByte[i] < 0x10){
 Serial.print(" 0");
 }
 else{
 Serial.print(" ");
 }
 Serial.print(mfrc522.uid.uidByte[i], HEX);// Printa a mensagem
//convertida em hexadecimal
 if(mfrc522.uid.uidByte[i] < 0x10){
conteudo.concat(String(" 0"));
 }
 else{
 conteudo.concat(String(" "));
 }
 conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
 }
 Serial.println();
 conteudo.toUpperCase();//Coloca todas as letras da string em
//maiúscula
 if (conteudo.substring(1) == "F3 7A EA 11") {
 Serial.println("Acesso Permitido!");
 digitalWrite(ledRed, LOW);
 digitalWrite(ledgreen, HIGH);
 delay(10000);
 digitalWrite(ledgreen, LOW);
 erro = 0;
 }if(conteudo.substring(1) != "F3 7A EA 11"){
 erro ++;
 Serial.println("Acesso Negado!");
    digitalWrite(ledRed, LOW);
    delay(500);
    digitalWrite(ledRed, HIGH);
    delay(500);
    digitalWrite(ledRed, LOW);
    delay(500);
    digitalWrite(ledRed, HIGH);
    delay(500);
    digitalWrite(ledRed, LOW);
    delay(500);
    digitalWrite(ledRed, HIGH);
    delay(500);
 }
 if(erro >= 5){
  int tempo = 30000;
  tone(7,528,tempo);
    
    for(int i=0;i<=30;i++){
    digitalWrite(ledRed, LOW);
    delay(500);
    digitalWrite(ledRed, HIGH);
    delay(500);
    //int tempo = 30000;
   // tone(7,528,tempo);
    }
    //int tempo = 30000;
    //tone(7,528,tempo);
    erro = 0;
 }

 
 delay(1000);
}
