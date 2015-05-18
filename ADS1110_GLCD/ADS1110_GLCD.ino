/*
 * NAVARRO ELETRÔNICA 
 * MULTIMETRO COM LCD GRÁFICO E ADS1110
 *
 * http://www.youtube.com/c/Navarroeletrônica
 * www.navarroeletronica.com
 * contato@navarroeletronica.com
 */

#include <Wire.h> //Biblioteca I2C para comunicação com o ADS1110
#include <openGLCD.h> //Biblioteca OpenGLCD

#define ads1110 0x48 //Utilizamos um define para facilitar a troca do ADS caso compre outro

float voltage,data;
byte highbyte, lowbyte, configRegister;
  
void setup()
{
 
  GLCD.Init();
  GLCD.SelectFont(System5x7);
  
  Wire.begin();//Start na biblioteca wire
   
  //Mensagem de boas vindas abaixo
  GLCD.print("NAVARRO");
  GLCD.CursorTo(0,2); 
  GLCD.print("ELETRONICA");
 
  delay(3000); 
  GLCD.ClearScreen(); 
}

void loop()
{
  GLCD.ClearScreen(); // Limpe a tela toda vez que for executar o loop principal 
  
  Wire.requestFrom(ads1110, 3); 
    while(Wire.available())//toda a informação deve chegar
    {
      highbyte = Wire.read(); // highbyte
      lowbyte = Wire.read(); // low byte
      configRegister = Wire.read();
    }
  
  data = highbyte * 256;
  data = data + lowbyte;
  voltage = data * 2.048;
  voltage = voltage / 32768.0; 
  voltage = voltage * 1000;
  
  GLCD.CursorTo(0,0);
  GLCD.print("MULTIMETRO NAVARRO");
  GLCD.CursorTo(0,2); 
  GLCD.print("TENSAO :"); GLCD.CursorTo(8,2);
  GLCD.PrintNumber(voltage);
  GLCD.print("mV");
  
  delay(1000);
}
