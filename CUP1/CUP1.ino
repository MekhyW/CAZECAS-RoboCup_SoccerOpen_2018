

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
 digitalWrite(CHUTE, HIGH);
  
  
}

void loop() {

ESTADOBOTAO = digitalRead(BOTAO);
//LED TESTE
digitalWrite(LED_G, HIGH);
delay(500);
digitalWrite(LED_Y, HIGH);
delay(500);
digitalWrite(LED_R, HIGH);
delay(500);
digitalWrite(LED_G, LOW);
delay(500);
digitalWrite(LED_Y, LOW);
delay(500);
digitalWrite(LED_R, LOW);
delay(500);


if(ESTADOBOTAO == LOW){

  
//MOTOR 1 TESTE
digitalWrite(M1A1, HIGH);
analogWrite(M1A2, 178);//70%
delay(2000);
digitalWrite(M1A1, LOW);
analogWrite(M1A2, 76);//30%
delay(2000);
  
//MOTOR 2 TESTE
digitalWrite(M2A1, HIGH);
analogWrite(M2A2, 178);
delay(2000);
digitalWrite(M2A1, LOW);
analogWrite(M2A2, 76);
delay(2000);


//MOTOR 3 TESTE
digitalWrite(M3A1, HIGH);
analogWrite(M3A2, 178);
delay(2000);
digitalWrite(M3A1, LOW);
analogWrite(M3A2, 76);
delay(2000);

  
//MOTOR 4 TESTE
digitalWrite(M4A1, HIGH);
analogWrite(M4A2, 178);
delay(2000);
digitalWrite(M4A1, LOW);
analogWrite(M4A2, 76);
delay(2000);

  
//MOTOR DRIBLE TESTE
digitalWrite(DRIBLE1, HIGH);
analogWrite(DRIBLE2, 178);
delay(2000);
digitalWrite(DRIBLE1, LOW);
analogWrite(DRIBLE2, 76);
delay(2000);


//CHUTE TESTE
digitalWrite(CHUTE, LOW);
delay(100);
digitalWrite(CHUTE, HIGH);
delay(900);
}
}

