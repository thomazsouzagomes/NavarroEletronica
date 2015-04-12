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
PIN 9 - LIGA/DESLIGA AQUECIMENTO
PIN 8 - Ar Condicionado

Sensor
PIN A0 - Entrada da tensão do LM35
PIN A1 - Entrada do Potênciometro para Setar o Setpoint

Saídas
PIN 10 - Saída Relé AQUECIMENTO
PIN 11 - Saída Relé VENTILADOR

PRONTO PARA TESTE
NÃO TESTADO AINDA
****************************************************************/

int sensor = A0;
int pot = A1;
int esquenta_ = 10;
int esfria_ = 11;
int setpoint, temperatura, sensor_RD, setpoint_RD;
int aquecimento, arcondicionado;

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  /*
  Rotina de Setup e boas vindas do display apenas para fins 
  cosméticos
  */
  aquecimento = 0; arcondicionado = 0;
  
  attachInterrupt(0, aquece, FALLING);
  attachInterrupt(1, esfria, FALLING);
  
  pinMode(esquenta_, OUTPUT); //saída do relé para acionar o aquecedor
  pinMode(esfria_, OUTPUT); //saída do relé para acionar o ar condicionado
  
  lcd.begin(16,2);
    
  lcd.print("NAVARRO"); //Início da mensagem de boas vindas
  lcd.setCursor(0, 1);
  lcd.print("ELETRONICA");
  //Utilizando for ao invés do Delay porque estamos usando a biblioteca timerone
  lcd.setCursor(0,0);
  lcd.print("TERMOSTATO");
  lcd.setCursor(0, 1);
  lcd.print("UNIVERSAL");//Final da mensagem de boas vindas
  delay(5000);
}

void loop()
{
  setpoint_RD = analogRead(pot);
  setpoint = map(setpoint_RD, 0, 1023, 10, 40);
  sensor_RD = analogRead(sensor);
  temperatura = (500*sensor_RD)/1023; //Transforma a leitura do LM35 no pino A0

  lcd.setCursor(0,0); lcd.print("TEMPERATURA:"); lcd.setCursor(13,0); lcd.print(temperatura); //Temperatura ambiente
  lcd.setCursor(0,1); lcd.print("SETPOINT"); lcd.setCursor(13,0); lcd.print(setpoint); //Temperatura setada
  
  //Caso esteja mais quente e o ar condicionado esteja ativo
  if(temperatura > setpoint + 2 && arcondicionado == 1)
  {
    digitalWrite(esfria_, HIGH);
  }
  else
  {
    digitalWrite(esfria_, LOW); digitalWrite(esquenta_, LOW);
  }
  //Caso esteja mais frio e o aquecimento esteja ativo
  if(temperatura < setpoint - 2 && aquecimento == 1)
  {
    digitalWrite(esquenta_, HIGH);
  }
  else
  {
    digitalWrite(esfria_, LOW); digitalWrite(esquenta_, LOW);
  }
  
  //Rotina de erro para caso a pessoa tente ligar o resfriamento e o ar condicionado ao mesmo tempo
  if(aquecimento == 1 && arcondicionado == 1){
    digitalWrite(esquenta_, LOW);
    digitalWrite(esfria_, LOW);
    lcd.setCursor(0,0); lcd.print("SELECIONE APENAS");lcd.setCursor(0,1);lcd.print("AQUECI OU ARCOND");
    delay(1000);
  }
}
  
/*****************************************************************
Rotina de ligar o aquecimento
*****************************************************************/
void aquece()
{
  aquecimento = ~aquecimento;
  lcd.setCursor(0,0); lcd.print("AQUECIMENTO"); lcd.setCursor(0,1);
  if(aquecimento == 1)
    {
    lcd.print("LIGADO");
    }
  else
    {
    lcd.print("DESLIGADO");  
    }
}

/*****************************************************************
Rotina de ligar o Ar-Condicionado
*****************************************************************/
void esfria()
{
  arcondicionado = ~arcondicionado;
  lcd.setCursor(0,0); lcd.print("ARCONDICIONADO"); lcd.setCursor(0,1);
  if(arcondicionado == 1)
    {
    lcd.print("LIGADO");
    }
  else
    {
    lcd.print("DESLIGADO");  
    }
} 
