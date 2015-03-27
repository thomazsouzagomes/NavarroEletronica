/*
Aula 1.1

Trabalhando com o IF
Nessa aula iremos aprender a realizar a leitura
do status de um botão e através desse status
ligar ou desligar um LED.

Você irá precisar apenas de um ARDUINO e um botão
que pode ser retirado de qualquer sucata disponível

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
       digitalWrite(LED, HIGH); // Liga o LED
     }
  }
  
/*
Lembrando que outras estruturas de controle
possuem uso similar e iremos falar sobre elas
em uma próxima aula.
*/
