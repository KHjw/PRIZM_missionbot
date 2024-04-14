# 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino"
# 2 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino" 2

//========================== main func ==========================
void setup(){
  prizm.PrizmBegin();
  Serial.begin(115200);
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 7 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 7 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino"
              "\n\n[[[Setup Start]]]\n\n"
# 7 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino" 3
              ); &__c[0];}))
# 7 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino"
              ))); // 세팅완료 메시지
  motorInit();
  huskeylensInit();
  battVoltagePrint();
  linetrace_analogSetting(3.0, 60, 40, 35);
  // linetrace_analogSetting(0.7, 25, 40, 35);

  Get_Avoid_Return(COLA, MONSTER, GREEN);

  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 16 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 16 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino"
              "\n\n[[[Setup Finish]]]\n\n"
# 16 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino" 3
              ); &__c[0];}))
# 16 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino"
              ))); // 세팅완료 메시지
}

void loop() {
  // battVoltagePrint(1000);
  // setBattVoltage2(12.8);

  MissionStart();
}
# 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/battry.ino"
// robot State Check
void battVoltagePrint(){
  int battVoltage = prizm.readBatteryVoltage();
  Serial.println("battVoltage : "+(String)(battVoltage/100)+"."+(String)(battVoltage%100)+"V"); // 현 배터리 전압 체크
}

void battVoltagePrint(int time){
  int battVoltage = prizm.readBatteryVoltage();
  Serial.println("battVoltage : "+(String)(battVoltage/100)+"."+(String)(battVoltage%100)+"V"); // 현 배터리 전압 체크
  delay(time);
}

void setBattVoltage2(float setVoltage){
  int time = 5000;
  battVoltagePrint();
  float battVoltage = prizm.readBatteryVoltage()/100.0;
  if(battVoltage > setVoltage){
    Serial.print("> battVoltage TOO HIGH");
    prizm.setMotorPowers(120,120);
  }
  else if(battVoltage < setVoltage-0.2){
    delay(1000);
    if(battVoltage >= setVoltage-0.2)
      time = 500;
    Serial.print("> battVoltage TOO LOW :: CHARGE RECOMMENDED");
    prizm.setMotorPowers(125,125);
  }
  else{
    Serial.print("> battVoltage JUST RIGHT");
    prizm.setMotorPowers(125,125);
    time = 500;
  }
  Serial.println("  Optimal setting : "+(String)(setVoltage));
  delay(time);
}
# 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
void huskeylensInit(){
  Wire.begin();
  while(!huskylens.begin(Wire)){
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 4 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 4 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
                  "Begin failed!"
# 4 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
                  ); &__c[0];}))
# 4 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
                  )));
    delay(100);
  }
}

void check_1NODE_Far(){
  int sonic_data = 0;
  int checkNUM = 3;
  for(int i = 0; i < checkNUM; i++){
    sonic_data += prizm.readSonicSensorCM(4);
    delay(100);
  }
  sonic_data = sonic_data / checkNUM;
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 17 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 17 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
              "sonic data : "
# 17 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
              ); &__c[0];}))
# 17 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
              )));
  Serial.println(sonic_data);
  if(48 < sonic_data && sonic_data <= 58){
    if(isObjectTarget()) NODE_dataUpdate(NODE3, 1);
    else NODE_dataUpdate(NODE3, 2);
  }
  else
    NODE_dataUpdate(NODE3, 0);
}

void check_1NODE_Near(){
  int sonic_data = 0;
  int checkNUM = 3;
  for(int i = 0; i < checkNUM; i++){
    sonic_data += prizm.readSonicSensorCM(4);
    delay(100);
  }
  sonic_data = sonic_data / checkNUM;
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 35 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 35 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
              "sonic data : "
# 35 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
              ); &__c[0];}))
# 35 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
              )));
  Serial.println(sonic_data);
  if(3 < sonic_data && sonic_data <= 15){
    if(isObjectTarget()) NODE_dataUpdate(NODE7, 1);
    else NODE_dataUpdate(NODE7, 2);
  }
  else
    NODE_dataUpdate(NODE7, 0);
}

void check_2NODE(int node_near, int node_far){
  int sonic_data = 0;
  int checkNUM = 3;
  for(int i = 0; i < checkNUM; i++){
    sonic_data += prizm.readSonicSensorCM(4);
    delay(100);
  }
  sonic_data = sonic_data / checkNUM;
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 53 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 53 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
              "sonic data : "
# 53 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
              ); &__c[0];}))
# 53 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
              )));
  Serial.println(sonic_data);
  if(11 < sonic_data && sonic_data <= 19){
    if(isObjectTarget()) NODE_dataUpdate(node_near, 1);
    else NODE_dataUpdate(node_near, 2);
  }
  else if(50 < sonic_data && sonic_data <= 60){
    NODE_dataUpdate(node_near, 0);
    if(isObjectTarget()) NODE_dataUpdate(node_far, 1);
    else NODE_dataUpdate(node_far, 2);
  }
  else{
    NODE_dataUpdate(node_near, 0);
    NODE_dataUpdate(node_far, 0);
  }
  ptrCurrentMode = NODE_PrintAll;
}

bool isObjectTarget(){
  int id_detected = 0;
  while(id_detected == 0){
    if(ReturnObjectCNT() < 2){
      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 75 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 75 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
                  "Object CNT == 1 / "
# 75 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
                  ); &__c[0];}))
# 75 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
                  )));
      id_detected = IdReturn();
    }
    else{
      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 79 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 79 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
                  "Object CNT >= 2 / "
# 79 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
                  ); &__c[0];}))
# 79 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
                  )));
      id_detected = IdReturn_Closer();
    }
  }
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 83 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 83 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
              "detected id : "
# 83 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
              ); &__c[0];}))
# 83 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
              )));
  Serial.println(id_detected);
  if(id_detected == target_object) return true;
  else return false;
}

int ReturnSquareSize(){
  int zeroCount = 0; // 인식된 객체가 없는 상황을 카운트하는 변수

  while (true) {
    if (!huskylens.request() || !huskylens.isLearned() || !huskylens.available()) {
      zeroCount++; // 조건에 맞지 않는 경우 카운트 증가
      if (zeroCount >= 3)
        return 0; // 3회 연속으로 객체가 인식되지 않은 경우 0을 반환
      continue; // 조건에 맞지 않으면 계속 반복
    }
    int maxSquare = 0; // 최대 크기 저장 변수 초기화
    zeroCount = 0; // 인식된 객체가 있으므로 카운터를 리셋
    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      int currentSquare = result.width * result.height; // 현재 객체의 크기 계산
      if (currentSquare > maxSquare) // 현재 객체가 지금까지 발견된 가장 큰 객체보다 크면
        maxSquare = currentSquare; // 최대 크기를 현재 객체 크기로 업데이트
    }
    if (maxSquare > 0)
      return maxSquare; // 가장 큰 객체의 크기 반환
  }
}


int IdReturn(){
  if (!huskylens.request())
    return 0;
  else if (!huskylens.isLearned())
    return 0;
  else if (!huskylens.available())
    return 0;
  else{
    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      if (result.command == COMMAND_RETURN_BLOCK) {
        if (result.ID == 1 || result.ID == 2 || result.ID == 3) {
          Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 125 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 125 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
                      "Block ID="
# 125 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino" 3
                      ); &__c[0];}))
# 125 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
                      )));
          Serial.println(result.ID);
          return result.ID;
        }
      }
    }
  }
  return 0; // 반환할 객체 ID가 없으면 0을 반환
}

int IdReturn_Closer(){
  if (!huskylens.request())
    return 0;
  else if (!huskylens.isLearned())
    return 0;
  else if (!huskylens.available())
    return 0;
  else {
    int maxArea = 0;
    int idOfLargest = 0;

    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      int area = result.width * result.height;
      if (area > maxArea) {
        maxArea = area;
        idOfLargest = result.ID;
      }
    }
    return idOfLargest;
  }
}

int ReturnObjectCNT() {
  if (!huskylens.request())
    return 0;
  else if (!huskylens.isLearned())
    return 0;
  else if (!huskylens.available())
    return 0;
  else {
    int objectCount = 0;
    while (huskylens.available()) {
      huskylens.read();
      objectCount++;
    }
    return objectCount;
  }
}
# 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
//******************************ANALOG Linetrace******************************
void linetrace_analogPrint(int time){
  int irData = analogRead(A1);
  if(irData > irDataMAX){ // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
    irData = irDataMAX;
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 6 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 6 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
                "irData calib -> "
# 6 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino" 3
                ); &__c[0];}))
# 6 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
                )));
  }
  Serial.print((String)(irData)+". ");
  if(testCNT > 10){
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 10 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 10 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
                  ""
# 10 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino" 3
                  ); &__c[0];}))
# 10 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
                  )));
    testCNT = 0;
  }
  testCNT ++;
  delay(time);
}

void linetrace_analog(){
  int irData = analogRead(A1);
  if(irData > irDataMAX){ // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
    irData = irDataMAX;
    // Serial.print("irData calib -> "); 
  }
  float sig = (irData-threshold)*gain;
  // Serial.print((String)(irData)+ " ("+(String)(sig)+"/"+(String)(default_speed-sig)+"). ");
  prizm.setMotorPowers(default_speed-sig, default_speed+sig);
  delay(20);
}

void linetrace_analogSetting(float gainData, int default_speedData, int irDataMAXData){
  gain = gainData;
  default_speed = default_speedData;
  irDataMAX = irDataMAXData;
  threshold = (irDataMAX + 19)/2+1;
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 34 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 34 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
              "LineTrace Setting:"
# 34 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino" 3
              ); &__c[0];}))
# 34 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
              ))); // 세팅값 입력
  Serial.println("irDataMAX:"+(String)(irDataMAX)+"  threshold:"+(String)(threshold)+"  default_speed:"+(String)(default_speed)+"  gain:"+(String)(gain));
}

void linetrace_analogSetting(float gainData, int default_speedData, int irDataMAXData, int thresholdData){
  gain = gainData;
  default_speed = default_speedData;
  irDataMAX = irDataMAXData;
  threshold = thresholdData;
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 43 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 43 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
              "LineTrace Setting:"
# 43 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino" 3
              ); &__c[0];}))
# 43 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
              ))); // 세팅값 입력
  Serial.println("irDataMAX:"+(String)(irDataMAX)+"  threshold:"+(String)(threshold)+"  default_speed:"+(String)(default_speed)+"  gain:"+(String)(gain));
}

// count
void intersectionDETECT(){
  if(prizm.readLineSensor(2) == 1){ // 검정에 닿았을 때
    intersectionCNT++;
    Serial.println("[[[intersectionDETECT]]] intersectionCNT : " + (String)(intersectionCNT)); // digitalDETECT 출력
    GoForward(60, 15);
  }
  delay(20);
}
# 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
void Get_Avoid_Return(int target_id, int false_id, int return_color){
  target_object = target_id;
  false_object = false_id;
  return_to = return_color;

  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 6 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 6 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
              "Mission Data Receved :: "
# 6 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
              ); &__c[0];}))
# 6 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
              )));
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 7 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 7 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
              "[ Target : "
# 7 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
              ); &__c[0];}))
# 7 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
              )));
  switch (target_object){
  case COLA:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 10 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 10 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "COLA"
# 10 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 10 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    // servo_maxDEG = 54;
    break;
  case MONSTER:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 14 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 14 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "MONSTER"
# 14 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 14 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    // servo_maxDEG = 54;
    break;
  case TEA:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 18 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 18 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "TEA"
# 18 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 18 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    // servo_maxDEG = 54;
    break;
  default:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 22 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 22 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "???"
# 22 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 22 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    break;
  }
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 25 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 25 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
              " / Avoid : "
# 25 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
              ); &__c[0];}))
# 25 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
              )));
  switch (false_object){
  case COLA:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 28 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 28 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "COLA"
# 28 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 28 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    break;
  case MONSTER:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 31 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 31 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "MONSTER"
# 31 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 31 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    break;
  case TEA:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 34 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 34 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "TEA"
# 34 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 34 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    break;
  default:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 37 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 37 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "???"
# 37 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 37 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    break;
  }
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 40 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 40 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
              " / Return to : "
# 40 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
              ); &__c[0];}))
# 40 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
              )));
  switch (return_color){
  case GREEN:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 43 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 43 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "GREEN"
# 43 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 43 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    break;
  case RED:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 46 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 46 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "RED"
# 46 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 46 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    break;
  case BLUE:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 49 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 49 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "BLUE"
# 49 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 49 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    break;
  default:
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 52 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 52 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "???"
# 52 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 52 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
    break;
  }
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 55 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 55 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                " ]"
# 55 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 55 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
}

//****************************** mission func ******************************
void MissionStart(){
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 60 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 60 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                "Mission Start!!!"
# 60 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 60 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
  move_StartPos();
  check_NODE3();
  NODE_PrintAll();
  StopFor(1000000);
}

void move_StartPos(){
  // GoForward(80, 700);       // 첫 번째 intersection 지날때 까지 boost
  move_1node();
  move_1node(); // NODE1 으로 이동
  currentNODE = NODE1; // 현재 위치 저장
  currnetNEWS = NORTH; // 현재 방향 저장
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 73 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 73 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                ">>> At Starting Position"
# 73 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 73 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
  StopFor(100);
}

void check_NODE3(){
  GoForward(100, 500);
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 79 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 79 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                ">>> CHECK FUNC :: check_NODE3"
# 79 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 79 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
  StopFor(0);
  check_1NODE_Far();
  switch (NODE_dataReturn(NODE3)){
  case 1:
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 84 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 84 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                  "NODE3 1"
# 84 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                  ); &__c[0];}))
# 84 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                  )));
    NODE_movement("2,3,2");
    break;
  case 2:
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 88 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 88 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                  "NODE3 2"
# 88 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                  ); &__c[0];}))
# 88 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                  )));
    NODE_movement("2,6,7,11,10,9,5");
    break;
  case 0:
    TurnRight();
    currnetNEWS = EAST;
    StopFor(200);
    check_NODE59();
    break;
  default:
    break;
  }
}

void check_NODE59(){
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 103 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 103 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                ">>> CHECK FUNC :: check_NODE5,9"
# 103 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 103 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
  check_2NODE(NODE5, NODE9);
  int N5 = NODE_dataReturn(NODE5);
  int N9 = NODE_dataReturn(NODE9);
  switch(N5){
  case 1:
    NODE_movement("5");
    break;
  case 2:
    TurnLeft();
    currnetNEWS = NORTH;
    StopFor(200);
    NODE_movement("2,6,7,11,10,9"); // exit 9
    break;
  case 0:
    switch (N9){
    case 1:
      while(prizm.readSonicSensorCM(4) > 10)
        linetrace_analog();
      canApproach();
      while(!isCanGrab)
        linetrace_analog();
      currentNODE = NODE9; // 현재 위치 저장
      currnetNEWS = EAST; // 현재 방향 저장 
      break;
    case 2:
      TurnLeft();
      currnetNEWS = NORTH;
      StopFor(200);
      NODE_movement("2,3,7,11,10,6,5");
      break;
    case 0:
      TurnLeft();
      currnetNEWS = NORTH;
      StopFor(200);
      NODE_movement("2");
      move_right();
      currnetNEWS = EAST;
      check_NODE610();
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

void check_NODE610(){
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 153 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 153 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                ">>> CHECK FUNC :: check_NODE6,10"
# 153 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino" 3
                ); &__c[0];}))
# 153 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
                )));
  check_2NODE(NODE6, NODE10);
  int N6 = NODE_dataReturn(NODE6);
  int N10 = NODE_dataReturn(NODE10);
  switch(N6){
  case 1:
    NODE_movement("6,5");
    break;
  case 2:
    TurnLeft();
    currnetNEWS = NORTH;
    NODE_movement("3,7,11,10,9");
    break;
  case 0:
    switch (N10){
    case 1:
      NODE_movement("6,10,9");
      break;
    case 2:
      NODE_movement("6,7,11,7,6,5");
      break;
    case 0:
      NODE_movement("6");
      move_left();
      currnetNEWS = NORTH;
      check_NODE7();
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

void check_NODE7(){
  check_1NODE_Near();
  switch (NODE_dataReturn(NODE7)){
  case 1:
    NODE_movement("7,6,5");
    break;
  case 2:
    GoForward(-40, 50);
    TurnRight();
    currnetNEWS = EAST;
    NODE_movement("10,11");
    GoForward(80, 200);
    move_180();
    currentNODE = NODE11;
    currnetNEWS = SOUTH;
    NODE_movement("10,9");
    break;
  default:
    break;
  }
}
# 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void motorInit(){
  prizm.setMotorInvert(1,1);

  prizm.setServoSpeed(1,60);
  prizm.setServoSpeed(2,60);
  prizm.setServoSpeed(3,10);

  gripper_openPOS();
}

//****************************** gripper mode ******************************
void gripper_openPOS(){
  prizm.setServoPosition(1,servo1_openPOS);
  prizm.setServoPosition(2,servo2_openPOS);
}

void gripper_closePOS(){
  prizm.setServoPosition(1,servo1_closePOS);
  prizm.setServoPosition(2,servo2_closePOS);
}

void gripper_moveUP(int time){
  prizm.setServoPosition(1,servo1_closePOS);
  prizm.setServoPosition(2,servo2_closePOS);
  prizm.setServoPosition(3,servo3_upPOS);
  delay(time);
}

//****************************** can grab ******************************
void canGrab(){
  if(!isCanGrab){
    if(prizm.readSonicSensorCM(4) <= 3){
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 33 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 33 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
                    "!!!Can Detected!!!"
# 33 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino" 3
                    ); &__c[0];}))
# 33 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
                    )));
      StopFor(50);
      gripper_moveUP(1000);
      isCanGrab = true;
      NODE_dataUpdate(currentNODE, 1);
      if(NODE_dataReturn(NODE11) == 1 || NODE_dataReturn(NODE5) == 1)
        intersectionCNT == 1;
      StopFor(2000);
    }
  }
}

void canApproach(){
  if(!isCanGrab){
    StopFor(100);
    if(ReturnSquareSize() > 1450){
      Serial.println(ReturnSquareSize());
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 50 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 50 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
                    "!!!Can Approach!!!"
# 50 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino" 3
                    ); &__c[0];}))
# 50 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
                    )));
      linetrace_analogSetting(0.7, 15, 40, 35);
      while(!isCanGrab && intersectionCNT == 0){
        canGrab();
        intersectionDETECT();
        linetrace_analog();
      }
      linetrace_analogSetting(3.0, 60, 40, 35);
    }
    else
      Serial.println(ReturnSquareSize());
  }
}

//****************************** move mode ******************************
void TurnRight(){
  prizm.setMotorPowers(40, -40);
  delay(750);
  prizm.setMotorPowers(125, 125); // 정지
  TurnCalib();
}

void TurnLeft(){
  prizm.setMotorPowers(-40, 40);
  delay(750);
  prizm.setMotorPowers(125, 125); // 정지
  TurnCalib();
}

void TurnAround(){
  prizm.setMotorPowers(100, -100);
  delay(1050);
  prizm.setMotorPowers(125, 125); // 정지
  TurnCalib();
}

void GoForward(int velocity, int time){
  prizm.setMotorPowers(velocity, velocity);
  delay(time);
}

void StopFor(unsigned long time){
  prizm.setMotorPowers(125, 125); // 정지
  delay(time);
}

void TurnCalib(){
  StopFor(50);
  intersectionDETECT();
  if(intersectionCNT > 0){
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 100 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 100 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
                  "TurnCalib"
# 100 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino" 3
                  ); &__c[0];}))
# 100 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
                  )));
    prizm.setMotorPowers(40, -40);
    delay(50);
    StopFor(50);
  }
  intersectionCNT = 0;
}

//****************************** return home ******************************
void return_from9(){
  if(return_to == GREEN){
  }
  else if(return_to == RED){
  }
  else if(return_to == BLUE){
  }
  // can drop
}

void return_from5(){
  if(return_to == GREEN){
  }
  else if(return_to == RED){
  }
  else if(return_to == BLUE){
  }
  // can drop
}

void return_from1(){
  if(return_to == GREEN){
  }
  else if(return_to == RED){
  }
  else if(return_to == BLUE){
  }
  // can drop
}
# 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
//****************************** NODE data ******************************
void NODE_to_Arr(int nodeNUM, int& row, int& col){
  row = nodeNUM / 3; // 행 위치 계산후 저장
  col = nodeNUM % 3; // 열 위치 계산후 저장
}

int NODE_dataReturn(int nodeNUM){
  NODE_to_Arr(nodeNUM, row, col);
  return nodeDataArr[row][col];
}

void NODE_dataPrint(int nodeNUM){
  NODE_to_Arr(nodeNUM, row, col);
  int nodeNum_data = nodeNumArr[row][col];
  int nodeData_data = nodeDataArr[row][col];
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 16 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 16 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              "[[NODE"
# 16 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              ); &__c[0];}))
# 16 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              )));
  Serial.print(nodeNum_data);
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 18 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 18 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              " data : "
# 18 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              ); &__c[0];}))
# 18 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              )));
  Serial.print(nodeData_data);
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 20 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 20 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                " ]]"
# 20 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                ); &__c[0];}))
# 20 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                )));
}

void NODE_dataUpdate(int nodeNUM, int data){
  NODE_to_Arr(nodeNUM, row, col);
  nodeDataArr[row][col] = data;
  NODE_dataPrint(nodeNUM);
}

int NODE_convert(int node_num){
  switch (node_num){
  case 1:
    return NODE1;
  case 2:
    return NODE2;
  case 3:
    return NODE3;
  case 5:
    return NODE5;
  case 6:
    return NODE6;
  case 7:
    return NODE7;
  case 9:
    return NODE9;
  case 10:
    return NODE10;
  case 11:
    return NODE11;
  default:
    return 0; // Added default return value
  }
}

void NODE_PrintAll(){
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 55 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 55 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                "\nNODE DATA PRINT"
# 55 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                ); &__c[0];}))
# 55 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                )));
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      String node_data = String(nodeDataArr[i][j]);
      if(node_data == "7") node_data = "?";
      Serial.print(node_data);
      if(j<2) Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 61 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                          (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 61 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                          " . "
# 61 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                          ); &__c[0];}))
# 61 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                          )));
    }
    Serial.println("");
  }
}

//****************************** NODE move ******************************
void NODE_move(int to){
  NODE_move(currentNODE, to);
}

void NODE_move(int from, int to){
  NODE_to_Arr(from, row, col);
  int from_row = row;
  int from_col = col;
  NODE_to_Arr(to, row, col);
  int to_row = row;
  int to_col = col;
  int row_move = from_row-to_row;
  int col_move = to_col-from_col;
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 81 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 81 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              "NODE_move / from:"
# 81 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              ); &__c[0];}))
# 81 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              )));
  Serial.print(from_row);
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 83 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 83 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              ","
# 83 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              ); &__c[0];}))
# 83 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              )));
  Serial.print(from_col);
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 85 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 85 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              " / to:"
# 85 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              ); &__c[0];}))
# 85 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              )));
  Serial.print(to_row);
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 87 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 87 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              ","
# 87 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              ); &__c[0];}))
# 87 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              )));
  Serial.print(to_col);
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 89 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 89 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              " / "
# 89 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
              ); &__c[0];}))
# 89 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
              )));
  Serial.println(row_move*10 + col_move);
  currentNODE = to;
  switch(row_move*10 + col_move){
    case 00:
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 94 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 94 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                    "move : stay"
# 94 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                    ); &__c[0];}))
# 94 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                    )));
      StopFor(100000);
      break;
    case 01:
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 98 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 98 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                    "move : EAST"
# 98 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                    ); &__c[0];}))
# 98 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                    )));
      move_NEWS(EAST);
      break;
    case -01:
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 102 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 102 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                    "move : WEST"
# 102 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                    ); &__c[0];}))
# 102 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                    )));
      move_NEWS(WEST);
      break;
    case 10:
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 106 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 106 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                    "move : NORTH"
# 106 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                    ); &__c[0];}))
# 106 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                    )));
      move_NEWS(NORTH);
      break;
    case -10:
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 110 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 110 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                    "move : SOUTH"
# 110 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                    ); &__c[0];}))
# 110 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                    )));
      move_NEWS(SOUTH);
      break;
    default:
      StopFor(100000);
      break;
  }
}

void move_NEWS(int news){
  switch(news - currnetNEWS){
    case 0:
      break;
    case 1:
    case -3:
      move_right();
      break;
    case -1:
    case 3:
      move_left();
      break;
    case 2:
    case -2:
      move_180();
      break;
  }
  currnetNEWS = news;
  canApproach();
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 138 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 138 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                "move_1node"
# 138 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                ); &__c[0];}))
# 138 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                )));
  move_1node();
}

//****************************** NODE movement ******************************
void NODE_movement(String input){
  movement_parsing(input);
  int movetotalCNT = moveCNT;
  while(moveCNT > 0){
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 147 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 147 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                "moveCNT:"
# 147 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino" 3
                ); &__c[0];}))
# 147 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
                )));
    Serial.println(moveCNT);
    int moveto = moveArr[movetotalCNT - moveCNT];
    NODE_move(NODE_convert(moveto));
    moveCNT--;
  }
  for (int i = 0; i < 15; i++)
    moveArr[i] = 0;
}

void movement_parsing(String input){
  int index = 0; // 배열 인덱스 초기화

  int pos = input.indexOf(','); // 쉼표로 구분된 숫자 추출  
  while (pos != -1 && moveCNT < 15) {
    moveArr[moveCNT++] = input.substring(index, pos).toInt(); // 숫자로 변환하여 저장
    index = pos + 1;
    pos = input.indexOf(',', index); // 다음 쉼표 위치 찾기
  }

  if (moveCNT < 15) // 마지막 숫자 처리
    moveArr[moveCNT++] = input.substring(index).toInt();

  for (int i = moveCNT; i < 15; i++) // 배열 나머지 부분을 0으로 채우기
    moveArr[i] = 0;
}

//****************************** move 1node ******************************
void move_1node(){
  while(intersectionCNT < 1){
    intersectionDETECT();
    linetrace_analog();
  }
  intersectionCNT = 0;
}

//****************************** simple move ******************************
void move_right(){
  StopFor(200);
  GoForward(60, 450);
  TurnRight();
  StopFor(700);
}

void move_left(){
  StopFor(200);
  GoForward(60, 380);
  TurnLeft();
  StopFor(700);
}

void move_180(){
  StopFor(200);
  GoForward(60, 400);
  TurnAround();
  StopFor(700);
}
