#define pinobotao 17

void EsperarBotao(){
  pinMode(pinobotao, INPUT);
  while(digitalRead(pinobotao) == HIGH){
		delay(1);
	}
}
