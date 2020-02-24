#include <SPI.h>
#include <Pixy.h>
Pixy pixy;
uint16_t blocks; //1=bola, 2=golAmarelo, 3=golAzul, 4=cantoverde, 5=cantovermelho, 6=cantociano, 7=cantoroxo
bool VendoBola=false;
bool PosseBola=false;
bool VendoGol=false;
bool GolAberto=false;
bool VendoCantoDireito=false;
bool VendoCantoEsquerdo=false;
int BolaX=0;
int BolaY=0;
int GolX=0;
int GolAltura=0;
int GolLargura=0;
int CantoDireitoX=0;
int CantoEsquerdoX=0;


void Pixy_Refrescar(){
  VendoBola=false;
  PosseBola=false;
  VendoGol=false;
  GolAberto=false;
  VendoCantoDireito=false;
  VendoCantoEsquerdo=false;
  for(int e=0;e<20;e++){
    blocks=pixy.getBlocks();
      for(int i=0; i<blocks; i++){
      if(pixy.blocks[i].signature==1){
        BolaX=map(pixy.blocks[i].x, 0, 319, 100, -100);
        BolaY=map(pixy.blocks[i].y, 0, 199, 100, -100);
        VendoBola=true;
        if(BolaY<=-76){
          PosseBola=true;
        }
      }
    }
    if(VendoBola==true){
      break;
    }
  }
  for(int e=0;e<20;e++){
    blocks=pixy.getBlocks();
    for(int i=0; i<blocks; i++){
      if((pixy.blocks[i].signature==2||pixy.blocks[i].signature==3) && (Orientacao<=90 || Orientacao>=270)){
        GolX=map(pixy.blocks[i].x, 0, 319, -100, 100);
        GolAltura=map(pixy.blocks[i].height, 0, 200, 0, 100);
        GolLargura=map(pixy.blocks[i].width, 0, 320, 0, 100);
        VendoGol=true;
        if(GolAltura>=31){
          GolAberto=true;
        }
      }
    }
    if(VendoGol==true){
      break;
    }
  }
  for(int e=0;e<20;e++){
    blocks=pixy.getBlocks();
    for(int i=0; i<blocks; i++){
      if((pixy.blocks[i].signature==5||pixy.blocks[i].signature==7)  && (Orientacao<=90 || Orientacao>=270)){
        VendoCantoDireito=true;
        CantoDireitoX=map(pixy.blocks[i].x, 0, 319, 100, -100);
      }
    }
    if(VendoCantoDireito==true){
      break;
    }
  }
  for(int e=0;e<20;e++){
    blocks=pixy.getBlocks();
    for(int i=0; i<blocks; i++){
      if((pixy.blocks[i].signature==4||pixy.blocks[i].signature==6)  && (Orientacao<=90 || Orientacao>=270)){
        VendoCantoEsquerdo=true;
        CantoEsquerdoX=map(pixy.blocks[i].x, 0, 319, 100, -100);
      }
    }
    if(VendoCantoEsquerdo==true){
      break;
    }
  }
  Serial.println(VendoBola);
  Serial.println(BolaX);
  delay(100);
}
