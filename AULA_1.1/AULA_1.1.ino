/*
Aula 1.1

Blink utilizando IF

*/

int LED = 13;
int B = 10;
int state = 1;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(B, INPUT);
}

void loop(){
  state = digitalRead(B); //Leia o estado do botão
  if(state = 0)
  {
       digitalWrite(LED, LOW); //Desliga o LED
     }
       else
     {
       digitalWrite(LED, HIGH);
     }
  }
