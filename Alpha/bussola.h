#include <HMC5883Llib.h>
Magnetometer compass;
float Orientacao=0;
float OrientacaoErro=0;

void Bussola_Refrescar(){
  double heading;
  compass.readHeadingDeg(&heading);
  Orientacao = heading;
  Orientacao -= OrientacaoErro;
  if(Orientacao<0){
    Orientacao += 360;
  }
}

void Bussola_Inicializar(){
    Wire.begin();
    compass.begin();
    compass.setGain(HMC5833L_GAIN_1370);
    for(int cont=0;cont<100;cont++){
      Bussola_Refrescar();
    }
    OrientacaoErro=Orientacao;
}
