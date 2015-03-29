/*
Aula 1.2

Trabalhando com o Switch-Case
Nessa aula iremos aprender a realizar a leitura
do status de um botão e através desse status
ligar ou desligar um LED.

Você irá precisar apenas de um ARDUINO e um botão
que pode ser retirado de qualquer sucata disponível

*/

int LED = 13;
int B = 10; //Botão
int state = 1;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(B, INPUT);
}

void loop(){
  state = digitalRead(B); //Leia o estado do botão 
    switch (state){
    case 1:
    digitalWrite(LED, LOW); // Caso o botão esteja em nível alto, o led deverá permanecer apagado
    break;
    case 0:
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
    break;
    }
  }
  
/*
Lembrando que outras estruturas de controle
possuem uso similar e iremos falar sobre elas
em uma próxima aula.
*/

