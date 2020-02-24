#include <NewPing.h>
int USAtras=60;
NewPing Atras(18, 19, 35);  //trig, echo, maxdist

void Ultrassom_Refrescar(){
  USAtras = Atras.ping_cm();
  if(USAtras==0){
    USAtras=99;
  }
}
