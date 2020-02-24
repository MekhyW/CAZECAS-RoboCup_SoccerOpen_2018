#define led1 14
#define led2 15
#define led3 0
float bateria = 0;                //tensao da bateria
int divisor=0;

void BateriaIndicador_Inicializar(){
  pinMode(led1, INPUT); //verde
  pinMode(led2, INPUT); //amarelo
  pinMode(led3, INPUT); //vermelho
}

void status_bat(){
  divisor = analogRead(A0);
  delay(50);
  bateria = divisor * 0.0032226563;
  //Serial.println(bateria, 3);
  if(bateria>=0.700){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
   }
  if(bateria>=0.6 && bateria<=0.699){
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
   }
  if(bateria<=0.599){
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,HIGH);
   }
}
