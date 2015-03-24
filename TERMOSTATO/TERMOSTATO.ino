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

Sensor
PIN A0 - Entrada da tensão do LM35

Saídas
PIN 10 - Saída Relé AQUECIMENTO
PIN 11 - Saída Relé VENTILADOR

WORK IN PROGRESS
WORK IN PROGRESS

****************************************************************/

int sensor = A0;
int esquenta = 10;
int esfria = 11;
int setpoint = 25;
int temperatura;

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  /*
  Rotina de Setup e boas vindas do display apenas para fins 
  cosméticos
  */
  attachInterrupt(0, sobe, FALLING);
  attachInterrupt(1, desce, FALLING);
  /*
  Rotina de interrupt acima
  */
  pinMode(esquenta, OUTPUT);
  pinMode(esfria, OUTPUT);
  lcd.begin(16,2);
  lcd.print("NAVARRO"); //Início da mensagem de boas vindas
  lcd.setCursor(0, 1);
  lcd.print("ELETRONICA");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("TERMOSTATO");
  lcd.setCursor(0, 1);
  lcd.print("UNIVERSAL");
  delay(2000);//Final da mensagem de boas vindas
}

void loop() {
 temperatura = (500*sensor)/1023; //Transforma a leitura do LM35 no pino A0
 lcd.setCursor(0,0); lcd.print("TEMPERATURA"); lcd.setCursor(13,0); lcd.print(temperatura); //Temperatura ambiente
 lcd.setCursor(0,1); lcd.print("SETPOINT"); lcd.setCursor(13,0); lcd.print(setpoint); //Temperatura setada

/*
Work in progress
*/
if(temperatura < setpoint - 5){
}
}
/*****************************************************************
Rotina de aumentar a temperatura de setpoint, não é necessário fazer a leitura do valor da temperatura
Fazemos uma nova impressão no display para mostrar a temperatura alvo no LCD
*****************************************************************/
void sobe()
  {
  setpoint = setpoint + 1;
  lcd.setCursor(0,0); lcd.print("TEMPERATURA"); lcd.setCursor(13,0); lcd.print(temperatura); //Temperatura ambiente
  lcd.setCursor(0,1); lcd.print("SETPOINT"); lcd.setCursor(13,0); lcd.print(setpoint); //Temperatura setada
  }

/*****************************************************************
Rotina de diminuir a temperatura de setpoint, não é necessário fazer a leitura do valor da temperatura
Fazemos uma nova impressão no display para mostrar a temperatura alvo no LCD
*****************************************************************/
void desce()
  {
  setpoint = setpoint - 1;
  lcd.setCursor(0,0); lcd.print("TEMPERATURA"); lcd.setCursor(13,0); lcd.print(temperatura); //Temperatura ambiente
  lcd.setCursor(0,1); lcd.print("SETPOINT"); lcd.setCursor(13,0); lcd.print(setpoint); //Temperatura setada
  }
