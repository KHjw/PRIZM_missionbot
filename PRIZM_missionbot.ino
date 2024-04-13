#include "PRIZM_missionbot.h"

//========================== main func ==========================
void setup(){
  prizm.PrizmBegin();
  Serial.begin(9600);
  motorInit();

  Serial.print("\n\n[[[[READY TO ROLL]]]\n\n");    // 세팅완료 메시지
  battVoltagePrint();
  linetrace_analogSetting(3.0, 60, 40, 35);
  
  ptrCurrentMode = move_StartBoost;
}

void loop() {
  // battVoltagePrint(1000);
  // setBattVoltage2(13.0);

  ptrCurrentMode();
}