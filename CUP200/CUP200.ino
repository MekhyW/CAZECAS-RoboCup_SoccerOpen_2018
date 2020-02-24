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
const int M1A1=8;
const int M1A2=9;
int M2A1=6; 
int M2A2=7;
int M3A1=2;
int M3A2=3;
int M4A1=4;
int M4A2=5;
int DRIBLE1=10;
int DRIBLE2=11;
int CHUTE=23;
int BOTAO=17;
int ESTADOBOTAO=0;
int libera=0;
int LED_G=14;
int LED_Y=15;
int LED_R=69;


void setup() {
 Serial.begin(9600);
  pinMode(M1A1 , OUTPUT);
  pinMode(M1A2 , OUTPUT); 
  pinMode(M2A1 , OUTPUT);
  pinMode(M2A2 , OUTPUT);
  pinMode(M3A1 , OUTPUT);
  pinMode(M3A2 , OUTPUT); 
  pinMode(M4A1 , OUTPUT);
  pinMode(M4A2 , OUTPUT); 
  pinMode(DRIBLE1 , OUTPUT);
  pinMode(DRIBLE2 , OUTPUT); 
  pinMode(CHUTE , OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y , OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BOTAO, INPUT);
  analogWrite(M2A2, 0);
  analogWrite(M1A2, 0);
  analogWrite(M3A2, 0);
  analogWrite(M4A2, 0);
  digitalWrite(CHUTE, HIGH);
  pixy.init();
  Serial.println("Press to start");
  while(digitalRead(BOTAO) == HIGH){
      Serial.println(digitalRead(BOTAO));
      delay(1);
  }
}

void nada(){
  Pixy_Refrescar();
  Serial.println(BolaX);
  delay(100);
}

void loop() {
  Pixy_Refrescar();
  if(VendoBola==true){
    while(BolaX>=50 && VendoBola==true){
      Pixy_Refrescar();
      digitalWrite(M2A1, LOW);
      digitalWrite(M1A1, HIGH);
      digitalWrite(M3A1, LOW);
      digitalWrite(M4A1, LOW);
      analogWrite(M2A2, 50);
      analogWrite(M1A2, 205);
      analogWrite(M3A2, 205);
      analogWrite(M4A2, 205);
    }
    while(BolaX<=(-50) && VendoBola==true){
      Pixy_Refrescar();
      digitalWrite(M2A1, HIGH);
      digitalWrite(M1A1, LOW);
      digitalWrite(M3A1, HIGH);
      digitalWrite(M4A1, HIGH);
      analogWrite(M2A2, 50);
      analogWrite(M1A2, 205);
      analogWrite(M3A2, 205);
      analogWrite(M4A2, 205);
    }
    digitalWrite(M2A1, LOW);
    digitalWrite(M1A1, HIGH);
    digitalWrite(M3A1, HIGH);
    digitalWrite(M4A1, HIGH);
    analogWrite(M2A2, 105);
    analogWrite(M1A2, 150);
    analogWrite(M3A2, 150);
    analogWrite(M4A2, 150);
  } else if(VendoBola==false) {
    digitalWrite(M2A1, HIGH);
    digitalWrite(M1A1, LOW);
    digitalWrite(M3A1, LOW);
    digitalWrite(M4A1, LOW);
    analogWrite(M2A2, 105);
    analogWrite(M1A2, 150);
    analogWrite(M3A2, 150);
    analogWrite(M4A2, 150);
  }
}


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
      if((pixy.blocks[i].signature==2||pixy.blocks[i].signature==3)){
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
      if((pixy.blocks[i].signature==5||pixy.blocks[i].signature==7)){
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
      if((pixy.blocks[i].signature==4||pixy.blocks[i].signature==6)){
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

