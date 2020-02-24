#define motorIE1 6
#define motorIE2 7
#define motorID1 2
#define motorID2 3
#define motorSE1 8
#define motorSE2 9
#define motorSD1 4
#define motorSD2 5
#define Dribbler1 10
#define Dribbler2 11
#define KickerPin 23

void Motores_Parar(){
    analogWrite(motorIE2, 0);
    analogWrite(motorID2, 0);
    analogWrite(motorSE2, 0);
    analogWrite(motorSD2, 0);
    analogWrite(Dribbler2, 0);
    digitalWrite(KickerPin, 1);
}

void Motores_Inicializar(){
  pinMode(motorIE2, OUTPUT);
  pinMode(motorID2, OUTPUT);
  pinMode(motorSE2, OUTPUT);
  pinMode(motorSD2, OUTPUT);
  pinMode(motorIE1, OUTPUT);
  pinMode(motorID1, OUTPUT);
  pinMode(motorSE1, OUTPUT);
  pinMode(motorSD1, OUTPUT);
  pinMode(Dribbler1, OUTPUT);
  pinMode(Dribbler2, OUTPUT);
  pinMode(KickerPin, OUTPUT);
}


void BaseVelocidade(int velocidade, int sentido){
  //1=frente, 2=tras, 3=esquerda, 4=direita, 5=horario, 6=antihorario
  if(sentido==1){
    digitalWrite(motorIE1, LOW);
    digitalWrite(motorSE1, HIGH);
    digitalWrite(motorID1, HIGH);
    digitalWrite(motorSD1, HIGH);
  } else if(sentido==2){
    digitalWrite(motorIE1, HIGH);
    digitalWrite(motorSE1, LOW);
    digitalWrite(motorID1, LOW);
    digitalWrite(motorSD1, LOW);
  } else if(sentido==3){
    digitalWrite(motorIE1, LOW);
    digitalWrite(motorSE1, LOW);
    digitalWrite(motorID1, LOW);
    digitalWrite(motorSD1, HIGH);
  } else if(sentido==4){
    digitalWrite(motorIE1, HIGH);
    digitalWrite(motorSE1, HIGH);
    digitalWrite(motorID1, HIGH);
    digitalWrite(motorSD1, LOW);
  } else if(sentido==5){
    digitalWrite(motorIE1, LOW);
    digitalWrite(motorSE1, HIGH);
    digitalWrite(motorID1, LOW);
    digitalWrite(motorSD1, LOW);
  } else if(sentido==6){
    digitalWrite(motorIE1, HIGH);
    digitalWrite(motorSE1, LOW);
    digitalWrite(motorID1, HIGH);
    digitalWrite(motorSD1, HIGH);
  }
  analogWrite(velocidade, motorIE2);
  analogWrite(velocidade, 255-motorSE2);
  analogWrite(velocidade, 255-motorID2);
  analogWrite(velocidade, 255-motorSD2);
}


void DribblerPull(){
  analogWrite(Dribbler1, LOW);
  analogWrite(Dribbler2, 255);
}

void DribblerPush(){
  analogWrite(Dribbler1, HIGH);
  analogWrite(Dribbler2, 255);
}

void DribblerStop(){
  analogWrite(Dribbler2, 0);
}

void Kick(){
  DribblerPush();
  delay(100);
  digitalWrite(KickerPin, 0); //expand
  delay(100);
  digitalWrite(KickerPin, 1); //retract
}
