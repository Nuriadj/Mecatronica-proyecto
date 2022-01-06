#include <SPI.h>

//-- Pin usado para la seleccion del esclavo
#define SS 5
#define yaxis 13
#define xaxis 33
#define led 2
#define k 32
#define a 39
#define b 26
#define c 34
#define d 27
void setup() {

  //-- Inicializar SPI
  SPI.begin();
  SPI.beginTransaction (SPISettings (4000000, MSBFIRST, SPI_MODE0));
  pinMode(SS, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(xaxis, INPUT);
  pinMode(yaxis, INPUT);
  pinMode(k, INPUT);
  pinMode(a, INPUT);
  pinMode(b, INPUT);
  pinMode(c, INPUT);
  pinMode(d, INPUT);
  Serial.begin(9600);
}

//-- Enviar un valor por el SPI para
//-- sacarlo por los LEDs de la FPGA
void write_LEDs(uint8_t value)
{
  digitalWrite(SS, LOW);
  SPI.transfer(value); 
  digitalWrite(SS, HIGH);
  delay(200);
  digitalWrite(SS, LOW);
  SPI.transfer(0x00); 
  digitalWrite(SS, HIGH);
  delay(50);
}

void loop() {
  int x = analogRead(xaxis);
  x = map(x, 0,4085,0,2);
  int y = analogRead(yaxis);
  y = map(y, 0,4085,0,2);
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  if (y == 2){
    write_LEDs(0x04);
  } else if (y == 0){
    write_LEDs(0x03);
  } else if (x == 2){
    write_LEDs(0x02);
  } else if (x == 0){
    write_LEDs(0x01);
  } else{
    write_LEDs(0x00);
  }

  if (digitalRead(k) == LOW){
    write_LEDs(0x80);
  }

  if (digitalRead(a) == LOW){
    write_LEDs(0x20);
  }

  if (digitalRead(c) == LOW){
    write_LEDs(0x60);
  }

  if (digitalRead(b) == LOW){
    write_LEDs(0x08);
  }

  if (digitalRead(d) == LOW){
    write_LEDs(0x18);
  }
  delay(100);

}
