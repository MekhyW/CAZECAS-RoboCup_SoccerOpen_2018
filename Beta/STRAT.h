void AnguloZero(){
  while(Orientacao<=180 && Orientacao>=10){
    BaseVelocidade(150, 6);
  }
  while(Orientacao>=180 && Orientacao<=350){
    BaseVelocidade(150, 5);
  }
}

void AlinharBola(){
  while(BolaX>=20){
    BaseVelocidade(150, 5);
  }
  while(BolaX<=(-20)){
    BaseVelocidade(150, 6);
  }
}

void AlinharBolaDefensivo(){
  BaseVelocidade(BolaX*4, 4);
}

void AlinharGol(){
  while(BolaX>=20){
    BaseVelocidade(150, 5);
  }
  while(BolaX<=(-20)){
    BaseVelocidade(150, 6);
  }
}

void Centralizar(){
  if(VendoCantoDireito==true && VendoCantoEsquerdo==true){
    BaseVelocidade((CantoEsquerdoX+CantoDireitoX)*4, 4);
  }
}



void Attack(){
  if(VendoBola==true){
    DribblerPull();
    if(PosseBola==true){
      if(VendoGol==true){
        BaseVelocidade(150, 1);
        AlinharGol();
        if(GolAberto==true){
          Kick();
        }
      } else {
        BaseVelocidade(150, 1);
        AnguloZero();
      }
    } else {
      BaseVelocidade(150, 1);
      AlinharBola();
    }
  } else {
    DribblerStop();
    BaseVelocidade(150, 2);
    AnguloZero();
    if(USAtras<=30){
      BaseVelocidade(150, 1);
    }
  }
}



void Defend(){
  AnguloZero();
  if(VendoBola==true){
    DribblerPull();
    AlinharBolaDefensivo();
  } else {
    DribblerStop();
    Centralizar();
  }
}
