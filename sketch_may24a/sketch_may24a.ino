void setup() {
  Serial.begin(9600);
  pinMode(23, OUTPUT);
  digitalWrite(23, 1);
  pinMode(A4, INPUT); //frente
  pinMode(A5, INPUT); //direita
  pinMode(A6, INPUT); //esquerda
  pinMode(A7, INPUT); //trás
}

void loop() {
  Serial.println(analogRead(A6));
}
