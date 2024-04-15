#include "PRIZM_missionbot.h"

//========================== main func ==========================
void setup() {
  prizm.PrizmBegin();
  Serial.begin(115200);
  Serial.print(F("\n\n[[[Setup Start]]]\n\n"));  // 세팅완료 메시지
  motorInit();
  huskeylensInit();
  battVoltagePrint();
  linetrace_analogSetting(3.0, 60, 40, 35);

  Get_Avoid_Return(COLA, TEA, GREEN);

  Serial.print(F("\n\n[[[Setup Finish]]]\n\n"));  // 세팅완료 메시지
}

void loop() {
  // battVoltagePrint(1000);
  // setBattVoltage2(12.8);  // 정상작동 배터리 전압 12.8 ~ 12.2

  MissionStart();
}