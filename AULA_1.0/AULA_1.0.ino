/*
Aula 1.0

Começando com o ARDUINO

Pisca de Led

*/

int LED = 13; //LED que já vem com o Arduino

//Este é um comentário de uma linha

void setup()
  {
  pinMode(LED, OUTPUT);
  }


void loop()
  {
  digitalWrite(LED, HIGH);
  delay(1000);    
  digitalWrite(LED, LOW);    
  delay(1000);              
  }
