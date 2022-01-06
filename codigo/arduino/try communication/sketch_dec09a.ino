#include <SPI.h>

#define yaxis 13
#define xaxis 33
#define SS 50

void setup() {
  //-- Inicializar SPI
  SPI.begin();
  SPI.beginTransaction (SPISettings (4000000, MSBFIRST, SPI_MODE0));
  // put your setup code here, to run once:
  pinMode(xaxis, INPUT);
  pinMode(yaxis, INPUT);
  pinMode(SS, OUTPUT);
  Serial.begin(9600);
}


//-- Enviar un valor por el SPI para
//-- sacarlo por los LEDs de la FPGA
void write_LEDs(uint8_t value)
{
  digitalWrite(SS, LOW);
  SPI.transfer(value); 
  digitalWrite(SS, HIGH);
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
void loop() {
  Serial.println("HI");
  int x = analogRead(xaxis);
  x = map(x, 0,4085,0,7);
  int y = analogRead(yaxis);
  y = map(y, 0,4085,0,7);
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  write_LEDs(y);
  delay(100);
  
  // put your main code here, to run repeatedly:

}
