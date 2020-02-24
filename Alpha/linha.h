#define CalibragemLinhaBranca 999
#define IVFrente A4
#define IVEsquerda A6
#define IVDireita A5
#define IVAtras A7
int ValIVFrente=0;
int ValIVTras=0;
int ValIVEsquerda=0;
int ValIVDireita=0;

void Linha_Inicializar(){
  pinMode(IVFrente, INPUT);
  pinMode(IVEsquerda, INPUT);
  pinMode(IVDireita, INPUT);
  pinMode(IVAtras, INPUT);
}

void Linha_Checar(){
  ValIVFrente = map(analogRead(IVFrente), 370, 1023, 0, 1000);
  ValIVTras = map(analogRead(IVAtras), 200, 1023, 0, 1000);
  ValIVDireita = map(analogRead(IVDireita), 25, 1023, 0, 1000);
  ValIVEsquerda = map(analogRead(IVEsquerda), 250, 1023, 0, 1000);
  if(ValIVFrente>CalibragemLinhaBranca){
    BaseVelocidade(150, 2);
    delay(500);
  } else if(ValIVEsquerda>CalibragemLinhaBranca){
    BaseVelocidade(150, 4);
    delay(500);
  } else if(ValIVDireita>CalibragemLinhaBranca){
    BaseVelocidade(150, 3);
    delay(500);
  } else if(ValIVTras>CalibragemLinhaBranca){
    BaseVelocidade(150, 1);
    delay(500);
  }
}
