#define motorIEback 6
#define motorIEfwd 7
#define motorIDback 3
#define motorIDfwd 2
#define motorSEfwd 8
#define motorSEback 9
#define motorSDfwd 4
#define motorSDback 5
int velIE=0;
int velID=0;
int velSE=0;
int velSD=0;
#define Dribblerpush 10
#define Dribblerpull 11
#define KickerPin 23


void Motores_Parar(){
    analogWrite(motorIEback, 0);
    analogWrite(motorIEfwd, 0);
    analogWrite(motorIDback, 0);
    analogWrite(motorIDfwd, 0);
    analogWrite(motorSEback, 0);
    analogWrite(motorSEfwd, 0);
    analogWrite(motorSDback, 0);
    analogWrite(motorSDfwd, 0);
    analogWrite(Dribblerpush, 0);
    analogWrite(Dribblerpull, 0);
    digitalWrite(KickerPin, 1);
}

void setup() {
  Serial.begin(9600);
  pinMode(17, INPUT); //botão
  pinMode(Dribblerpush, OUTPUT); //dribbler push
  pinMode(Dribblerpull, OUTPUT); //dribbler pull
  pinMode(KickerPin, OUTPUT); //kicker
  pinMode(motorIDfwd, OUTPUT); //motores:
  pinMode(motorIDback, OUTPUT);
  pinMode(motorSDfwd, OUTPUT);
  pinMode(motorSDback, OUTPUT); //pino defeituoso
  pinMode(motorIEback, OUTPUT);
  pinMode(motorIEfwd, OUTPUT);
  pinMode(motorSEfwd, OUTPUT);
  pinMode(motorSEback, OUTPUT);
  Motores_Parar(); 
}

void loop() {
  while(digitalRead(17) == HIGH){ //esperar botao
    delay(1);
  }
  BaseVelocidade(150, 1);
  delay(5000);
  Motores_Parar();
}


void BaseVelocidade(int velocidade, int sentido){
  //1=frente, 2=tras, 3=esquerda, 4=direita, 5=horario, 6=antihorario
  //chamar antes do Adicionar Velocidade
  if(sentido==1){
    velSE=velocidade;
    velSD=velocidade;
    velIE=velocidade;
    velID=velocidade;
  } else if(sentido==2){
    velSE=(-velocidade);
    velSD=(-velocidade);
    velIE=(-velocidade);
    velID=(-velocidade);
  } else if(sentido==3){
    velSE=(-velocidade);
    velSD=velocidade;
    velIE=velocidade;
    velID=(-velocidade);
  } else if(sentido==4){
    velSE=velocidade;
    velSD=(-velocidade);
    velIE=(-velocidade);
    velID=velocidade;
  } else if(sentido==5){
    velSE=velocidade;
    velSD=(-velocidade);
    velIE=velocidade;
    velID=(-velocidade);
  } else if(sentido==6){
    velSE=(-velocidade);
    velSD=velocidade;
    velIE=(-velocidade);
    velID=velocidade;
  }
  //escreve
  if(velSE<0){
    analogWrite(motorSEback, abs(velSE));
  } else {
    digitalWrite(motorSEfwd, abs(velSE));
  }
  if(velSD<0){
    analogWrite(motorSDback, abs(velSD*0.82));
  } else {
    analogWrite(motorSDfwd, abs(velSD*0.82));
  }
  if(velIE<0){
    analogWrite(motorIEback, abs(velIE));
  } else {
    analogWrite(motorIEfwd, abs(velIE));
  }
  if(velID<0){
    analogWrite(motorIDback, abs(velID*0.82));
  } else {
    analogWrite(motorIDfwd, abs(velID*0.82));
  }
  if(velocidade>0){
    AdicionarVelocidade(velocidade*0.06, 6);
    AdicionarVelocidade(velocidade*0.09, 4);
  }
}


void AdicionarVelocidade(int velocidade, int sentido){
  //1=frente, 2=tras, 3=esquerda, 4=direita, 5=horario, 6=antihorario
  if(sentido==1){
    velSE+=velocidade;
    velSD+=velocidade;
    velIE+=velocidade;
    velID+=velocidade;
  } else if(sentido==2){
    velSE-=velocidade;
    velSD-=velocidade;
    velIE-=velocidade;
    velID-=velocidade;
  } else if(sentido==3){
    velSE-=velocidade;
    velSD+=velocidade;
    velIE+=velocidade;
    velID-=velocidade;
  } else if(sentido==4){
    velSE+=velocidade;
    velSD-=velocidade;
    velIE-=velocidade;
    velID+=velocidade;
  } else if(sentido==5){
    velSE+=velocidade;
    velSD-=velocidade;
    velIE+=velocidade;
    velID-=velocidade;
  } else if(sentido==6){
    velSE-=velocidade;
    velSD+=velocidade;
    velIE-=velocidade;
    velID+=velocidade;
  }
  //impede overload (ainda será preciso tomar cuidado pra chamar cada add uma vez por loop)
  velSE=constrain(velSE, -255, 255);
  velSD=constrain(velSD, -255, 255);
  velIE=constrain(velIE, -255, 255);
  velID=constrain(velID, -255, 255);
  //escreve
  if(velSE<0){
    analogWrite(motorSEback, abs(velSE));
  } else {
    digitalWrite(motorSEfwd, abs(velSE));
  }
  if(velSD<0){
    analogWrite(motorSDback, abs(velSD*0.82));
  } else {
    analogWrite(motorSDfwd, abs(velSD*0.82));
  }
  if(velIE<0){
    analogWrite(motorIEback, abs(velIE));
  } else {
    analogWrite(motorIEfwd, abs(velIE));
  }
  if(velID<0){
    analogWrite(motorIDback, abs(velID*0.82));
  } else {
    analogWrite(motorIDfwd, abs(velID*0.82));
  }
}


void DribblerPull(){
  analogWrite(Dribblerpush, 0);
  analogWrite(Dribblerpull, 255);
}

void DribblerPush(){
  analogWrite(Dribblerpull, 0);
  analogWrite(Dribblerpush, 255);
}

void DribblerStop(){
  analogWrite(Dribblerpush, 0);
  analogWrite(Dribblerpull, 0);
}

void Kick(){
  DribblerPush();
  delay(100);
  digitalWrite(KickerPin, 0); //expand
  delay(100);
  digitalWrite(KickerPin, 1); //retract
}

