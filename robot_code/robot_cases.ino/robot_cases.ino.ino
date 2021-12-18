
#include <Stepper.h>
#define STEPS ?

int motorPinza= ?;
int motorRueda1= ?;
int motorRueda2= ?;

Stepper stepper(STEPS, ?, ?, ?, ?);

void setup() {
  // put your setup code here, to run once:
  
  int Pinza= 0;// 0-Cerrada 1-Abierta
  int dir_nema1= 1;// 1 o -1
  int dir_nema2= 1;// 1 o -1

  int vel_pinza= ?;//velocidad para la pinza
  int vel_mruedas= ?;// velocidad para las ruedas

  int mult_vel1= 1;//darle mas velocidad a la rueda 1 para que gire
  int mult_vel2= 1;//darle mas velocidad a la rueda 1 para que gire

  int max_time= 50; //Tiempo que va a estar cerrando o abriendo pinza en milisegundos
  int c_pinza= 0;// para saber si tiene que contar el tiempo o no
  unsigned long start_t_pinza;//tiempo en el que se comenzo a contar el tiempo

  pinMode(motorPinza, OUTPUT);
  pinMode(motorRueda1, OUTPUT);
  pinMode(motorRueda2, OUTPUT);
  stepper.setSpeed(?);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val;
  
  for(int i= 7; i >= 0; i--){
    val= bitRead(?, i);// lee un bit, i es la pos 0 es el menos signif (derecha)
    Serial.print(bitRead(?, i));

    //--- Pinza ----
    if (i == 7) and (val == 1){
      c_pinza= 1;
      start_time= millis();
      if(Pinza == 0){
        //definir la vel_pinza con su signo correpondiente
        Pinza= 1;
      }
      else{
        //definir la vel_pinza con su signo correpondiente
        Pinza= 0;
      }
    }
    // mas abajo se hace el analog write
    //---------------
    //-------------

    //--- Nema 1 ----
    
    if (i== 6){// Direccion
      dir_nema1= val;

      if(val== 0)
        dir_nema1= -1;
    }
    
    if (i== 5) and (val== 1){// Dar un paso 
      stepper.step(dir_nema1);
    }
    //---------------
    //--------------

    //--- Nema 2 ----
    
    if (i== 4){// Direccion
      dir_nema2= val;

      if(val== 0)
        dir_nema2= -1;
    }
    
    if (i== 3)and (val== 1){// Dar un paso 
      stepper.step(dir_nema2);
    }
    //---------------
    //--------------

    // ---Mover adelante Robot---
    if (i==2){
      vel_mruedas= vel_mruedas* val;// mas abajo se hace el analogwrite
    }

    //--- Girar a Izq---
    if (i==1){
      if(val)
        mult_vel1= 1.5;//factor por el que se multiplica la vel de la rueda 1
                      // para que vaya mas rapido y por lo tanto gire
      else
        mult_vel1= 1;
    }

    //--- Girar a Der---
    if(i==0){

      if(val)
        mult_vel2= 1.5;
      else
        mult_vel2= 1;
    }

    
    //--- Abrir o cerrar pinza ---
    if (c_pinza == 1){
      if((millis() - start_time) < max_time){
        analogWrite(motorPinza, );// hay que definir la velocidad de la pinza
      }
      else{
        analogWrite(motorPinza, 0);
        c_pinza= 0;
      }
    }

    val_sept= bitRead(?, 1);//valor bit septimo
    val_oct= bitRead(?, 0);//valor bit octavo

    if(val_sept) and (val_oct){// si ambos estan a 1
      vel_mruedas= vel_mruedas*(-1);//hacia atras
    }

    //-- Mover las ruedas---
    analogWrite(motorRueda1, vel_mruedas*mult_vel1);
    analogWrite(motorRueda2, vel_mruedas*mult_vel2);
    
  }

}
