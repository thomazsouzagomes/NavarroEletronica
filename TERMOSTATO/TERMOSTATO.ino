/****************************************************************
Termostato para diversos controles de Temperatura
Navarro Eletrônica

A intenção do projeto é fazer o ajuste de uma temperatura
Temos duas formas de modificar a temperatura nesse projeto:
Aquecendo através de uma resistência
Esfriando através de um ventilador

O Arduino deve acionar a resistência caso a temperatura esteja 
abaixo do setpoint e acionar o ventilador caso esteja acima.

MAPA DE PINOS:

Interface com o usuário
INT 0 - DIMINUI SET POINT
INT 1 - AUMENTA SET POINT
PIN 9 - LIGA/DESLIGA AQUECIMENTO

Sensor
PIN A0 - Entrada da tensão do LM35

Saídas
PIN 10 - Saída Relé AQUECIMENTO
PIN 11 - Saída Relé VENTILADOR

PRONTO PARA TESTE
NÃO TESTADO AINDA
****************************************************************/

int sensor = A0;
int esquenta = 10;
int esfria = 11;
int aquecimento = 9; //Botão para saber se o usuário deseja aquecimento ou não
int setpoint = 25;
int temperatura, sensorRD;

void printf();

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include <TimerOne.h>

void setup() {
  /*
  Rotina de Setup e boas vindas do display apenas para fins 
  cosméticos
  Rotina de interrupt
  */
  attachInterrupt(0, sobe, FALLING);
  attachInterrupt(1, desce, FALLING);
  /*
  Rotina da Biblioteca TimerOne
  */
  Timer1.initialize(500000);
  Timer1.attachInterrupt(lm35_read);
  
  pinMode(aquecimento, INPUT);
  pinMode(esquenta, OUTPUT);
  pinMode(esfria, OUTPUT);
  lcd.begin(16,2);
  
  
  /*
  Trecho comentado porque não consegui colocar o for para trabalhar aqui
  preciso revisar isso, delay não irá funcionar por causa da biblioteca TIMERONE
  
  
  lcd.print("NAVARRO"); //Início da mensagem de boas vindas
  lcd.setCursor(0, 1);
  lcd.print("ELETRONICA");
  //Utilizando for ao invés do Delay porque estamos usando a biblioteca timerone
  lcd.setCursor(0,0);
  lcd.print("TERMOSTATO");
  lcd.setCursor(0, 1);
  lcd.print("UNIVERSAL");//Final da mensagem de boas vindas
  for(x=1000; x > 0 ; x--){} //Utilizando for ao invés do Delay porque estamos usando a biblioteca timerone
  */
}

void loop() {
  sensorRD = analogRead(sensor);
  temperatura = (500*sensorRD)/1023; //Transforma a leitura do LM35 no pino A0
  printlcd(setpoint, temperatura);
}

void lm35_read(){
  sensorRD = analogRead(sensor);
  temperatura = (500*sensorRD)/1023; //Transforma a leitura do LM35 no pino A0
  int aquecimento_DR; //armazena o valor da chave aquecimento
  aquecimento_DR = digitalRead(aquecimento); 
  //Caso esteja mais quente
  if(temperatura > setpoint + 2){
    digitalWrite(esfria, HIGH);
  }
  else
  {
    digitalWrite(esfria,LOW); digitalWrite(esquenta,LOW);
  }
  //Caso esteja mais frio e o aquecimento esteja ativo
  if(temperatura < setpoint - 2 && aquecimento == 1){
    digitalWrite(esquenta,HIGH);
  }
  else
  {
    digitalWrite(esfria, LOW); digitalWrite(esquenta,LOW);
  }
}
  
/*****************************************************************
Rotina de display, coloquei em uma função a parte porque estava
repetindo ela no programa três vezes o.O
*****************************************************************/ 
void printlcd(int setpoint, int temperatura){
  lcd.setCursor(0,0); lcd.print("TEMPERATURA:"); lcd.setCursor(13,0); lcd.print(temperatura); //Temperatura ambiente
  lcd.setCursor(0,1); lcd.print("SETPOINT"); lcd.setCursor(13,0); lcd.print(setpoint); //Temperatura setada
}
/*****************************************************************
Rotina de aumentar a temperatura de setpoint, não é necessário fazer a leitura do valor da temperatura
Fazemos uma nova impressão no display para mostrar a temperatura alvo no LCD
*****************************************************************/
void sobe()
  {
  setpoint = setpoint + 1;
  printlcd(setpoint, temperatura);
  }

/*****************************************************************
Rotina de diminuir a temperatura de setpoint, não é necessário fazer a leitura do valor da temperatura
Fazemos uma nova impressão no display para mostrar a temperatura alvo no LCD
*****************************************************************/
void desce()
  {
  setpoint = setpoint - 1;
  printlcd(setpoint, temperatura);
  } 
