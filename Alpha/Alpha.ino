// VERSÃO 2.3NEW
#include <Wire.h>
#include "bateria.h"
#include "bussola.h"
#include "pixy.h"
#include "motores.h"
#include "ultrassonicos.h"
#include "linha.h"
#include "botao.h"
#include "STRAT.h"

void setup() {
  Serial.begin(38400);
  pinMode(pinobotao, INPUT);
  BateriaIndicador_Inicializar();
  Bussola_Inicializar();
  Motores_Inicializar();
  Linha_Inicializar();
  pixy.init();
  EsperarBotao();
}

void loop() {
  status_bat();
  Bussola_Refrescar();
  Pixy_Refrescar();
  Linha_Checar();
  Ultrassom_Refrescar();
  Attack();
}
