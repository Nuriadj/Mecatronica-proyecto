#include <SPI.h>

//-- Pin usado para la seleccion del esclavo
#define SS 5
#define led 1
void setup() {

  //-- Inicializar SPI
  SPI.begin();
  SPI.beginTransaction (SPISettings (4000000, MSBFIRST, SPI_MODE0));
  pinMode(SS, OUTPUT);
  pinMode(led, OUTPUT);
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

  //-- Sacar valor 0xAA por los LEDs
  write_LEDs(0x02);
  digitalWrite(led, HIGH);
  delay(5000);

  //-- Sacar valor 0x55 por los LEDs
  write_LEDs(0x01);
  digitalWrite(led, LOW);
  delay(5000);
}
