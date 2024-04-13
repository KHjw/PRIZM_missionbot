#include "PRIZM_missionbot.h"

//========================== main func ==========================
void setup(){
  prizm.PrizmBegin();
  Serial.begin(115200);
  Serial.print("\n\n[[[Setup Start]]]\n\n");    // 세팅완료 메시지

  motorInit();
  huskeylensInit();

  Get_Avoid_Return(COLA, MONSTER, GREEN);
  battVoltagePrint();
  linetrace_analogSetting(3.0, 60, 40, 35);

  Serial.print("\n\n[[[Setup Finish]]]\n\n");    // 세팅완료 메시지
}

void loop() {
  // battVoltagePrint(1000);
  // setBattVoltage2(12.8);
  // canGrab();
  move_StartPos();
  StopFor(1000000);
}