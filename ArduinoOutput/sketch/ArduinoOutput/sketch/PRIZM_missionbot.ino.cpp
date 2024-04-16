#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/ArduinoOutput/sketch/PRIZM_missionbot.ino.cpp"
#include <Arduino.h>
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino"
#include "PRIZM_missionbot.h"

//========================== main func ==========================
void setup() {
  prizm.PrizmBegin();
  Serial.begin(115200);
  Serial.print(F("\n\n[[[Setup Start]]]\n\n"));  // 세팅완료 메시지
  huskeylensInit();
  motorInit();
  battVoltagePrint();
  linetrace_analogSetting(3.0, 60, 40, 35);

  Get_Avoid_Return(COLA, TEA, GREEN);

  Serial.print(F("\n\n[[[Setup Finish]]]\n\n"));  // 세팅완료 메시지
}

void loop() {
  // battVoltagePrint(1000);
  // setBattVoltage2(12.8);  // 정상작동 배터리 전압 12.8 ~ 12.2

  // MissionStart();
  move_StartPos();
  check_NODE3();
}
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/battry.ino"
// robot State Check
void battVoltagePrint() {
  int battVoltage = prizm.readBatteryVoltage();
  Serial.print(F("battVoltage : "));
  Serial.print(battVoltage / 100);
  Serial.print(F("."));
  Serial.print(battVoltage % 100);
  Serial.println(F("V"));  // 현 배터리 전압 체크
}

void battVoltagePrint(int time) {
  int battVoltage = prizm.readBatteryVoltage();
  Serial.print(F("battVoltage : "));
  Serial.print(battVoltage / 100);
  Serial.print(F("."));
  Serial.print(battVoltage % 100);
  Serial.println(F("V"));  // 현 배터리 전압 체크
  delay(time);
}

void setBattVoltage2(float setVoltage) {
  int time = 5000;
  battVoltagePrint();
  float battVoltage = prizm.readBatteryVoltage() / 100.0;
  if (battVoltage > setVoltage) {
    Serial.print(F("> battVoltage TOO HIGH"));
    prizm.setMotorPowers(120, 120);
  } else if (battVoltage < setVoltage - 0.2) {
    delay(1000);
    if (battVoltage >= setVoltage - 0.2) time = 500;
    Serial.print(F("> battVoltage TOO LOW :: CHARGE RECOMMENDED"));
    prizm.setMotorPowers(125, 125);
  } else {
    Serial.print(F("> battVoltage JUST RIGHT"));
    prizm.setMotorPowers(125, 125);
    time = 500;
  }
  Serial.print(F("  Optimal setting : "));
  Serial.println(setVoltage);
  delay(time);
}
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"
void huskeylensInit() {
  Wire.begin();
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    gripper_closePOS();
    delay(100);
  }
  gripper_openPOS();
}

//****************************** check NODE ******************************
void check_1NODE(int node) {
  int SQ_size = ReturnSquareSize();
  int CNT = 0;
  while (SQ_size == 0) {
    if (CNT >= 3) break;
    CNT++;
    delay(50);
    SQ_size = ReturnSquareSize();
    Serial.print(F("SquareSizeCNT : "));
    Serial.println(CNT);
  }
  if (SQ_size > 100) {
    if (isObjectTarget())
      NODE_dataUpdate(node, 1);
    else
      NODE_dataUpdate(node, 2);
  } else
    NODE_dataUpdate(node, 0);
}

void check_1NODE_Far() {
  int ObjCNT = ReturnObjectCNT();
  int CNT = 0;
  while (ObjCNT == 0) {
    if (CNT >= 10) break;
    CNT++;
    delay(50);
    ObjCNT = ReturnObjectCNT();
    Serial.print(F("ObjcheckCNT : "));
    Serial.println(CNT);
  }
  if (ObjCNT > 0) {
    Serial.print(F("ReturnObjectCNT : "));
    Serial.println(ObjCNT);
    if (isObjectTarget())
      NODE_dataUpdate(NODE3, 1);
    else
      NODE_dataUpdate(NODE3, 2);
  } else {
    Serial.println(F("ReturnObjectCNT : 0"));
    NODE_dataUpdate(NODE3, 0);
  }
}

void check_1NODE_Near() {
  int ObjCNT = ReturnObjectCNT();
  int CNT = 0;
  while (ObjCNT == 0) {
    if (CNT >= 5) break;
    CNT++;
    delay(50);
    ObjCNT = ReturnObjectCNT();
    Serial.print(F("ObjcheckCNT : "));
    Serial.println(CNT);
  }
  if (ObjCNT > 0) {
    if (isObjectTarget())
      NODE_dataUpdate(NODE7, 1);
    else
      NODE_dataUpdate(NODE7, 2);
  } else
    NODE_dataUpdate(NODE7, 0);
}

void check_2NODE(int node_near, int node_far) {
  int SQ_size = ReturnSquareSize();
  Serial.print(F("ReturnSquareSize : "));
  Serial.println(SQ_size);
  if (SQ_size >= 5000) {
    if (isObjectTarget())
      NODE_dataUpdate(node_near, 1);
    else
      NODE_dataUpdate(node_near, 2);
  } else if (SQ_size >= 100 && SQ_size < 5000) {
    NODE_dataUpdate(node_near, 0);
    int ObjCNT = ReturnObjectCNT();
    int CNT = 0;
    while (ObjCNT == 0) {
      CNT++;
      if (CNT > 5) break;
      delay(100);
      ObjCNT = ReturnObjectCNT();
      Serial.print(F("ObjcheckCNT : "));
      Serial.println(CNT);
    }
    if (ObjCNT > 0) {
      if (isObjectTarget())
        NODE_dataUpdate(node_far, 1);
      else
        NODE_dataUpdate(node_far, 2);
    }
  } else {
    NODE_dataUpdate(node_near, 0);
    NODE_dataUpdate(node_far, 0);
  }
  ptrCurrentMode = NODE_PrintAll;
}

//****************************** object check ******************************
bool isObjectTarget() {
  int id_detected = 0;
  int CNT = 0;
  while (id_detected == 0) {
    CNT++;
    if (CNT > 5) break;
    id_detected = IdReturn_Closer();
  }
  Serial.print(F("detected id : "));
  Serial.println(id_detected);
  if (id_detected == target_object)
    return true;
  else
    return false;
}

int ReturnSquareSize() {
  int zeroCount = 0;  // 인식된 객체가 없는 상황을 카운트하는 변수
  while (true) {
    if (!huskylens.request() || !huskylens.isLearned() ||
        !huskylens.available()) {
      zeroCount++;  // 조건에 맞지 않는 경우 카운트 증가
      if (zeroCount >= 3)
        return 0;  // 3회 연속으로 객체가 인식되지 않은 경우 0을 반환
      continue;  // 조건에 맞지 않으면 계속 반복
    }
    int maxSquare = 0;  // 최대 크기 저장 변수 초기화
    zeroCount = 0;      // 인식된 객체가 있으므로 카운터를 리셋
    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      int currentSquare =
          result.width * result.height;  // 현재 객체의 크기 계산
      if (currentSquare >
          maxSquare)  // 현재 객체가 지금까지 발견된 가장 큰 객체보다 크면
        maxSquare = currentSquare;  // 최대 크기를 현재 객체 크기로 업데이트
    }
    if (maxSquare > 0) return maxSquare;  // 가장 큰 객체의 크기 반환
  }
}

int IdReturn() {
  if (!huskylens.request())
    return 0;
  else if (!huskylens.isLearned())
    return 0;
  else if (!huskylens.available())
    return 0;
  else {
    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      if (result.command == COMMAND_RETURN_BLOCK) {
        if (ReturnSquareSize() > 1000) {
          if (result.ID == TEA || result.ID == COLA) {
            Serial.print(F("Block ID="));
            Serial.println(result.ID);
            return result.ID;
          }
        }
      }
    }
  }
  return 0;  // 반환할 객체 ID가 없으면 0을 반환
}

int IdReturn_Closer() {
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

#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
//******************************ANALOG Linetrace******************************
void linetrace_analogPrint(int time) {
  int irData = analogRead(A1);
  if (irData >
      irDataMAX) {  // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
    irData = irDataMAX;
    Serial.print(F("irData calib -> "));
  }
  Serial.print((String)(irData) + ". ");
  if (testCNT > 10) {
    Serial.println(F(""));
    testCNT = 0;
  }
  testCNT++;
  delay(time);
}

void linetrace_analog() {
  int irData = analogRead(A1);
  // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
  if (irData > irDataMAX) irData = irDataMAX;
  float sig = (irData - threshold) * gain;
  prizm.setMotorPowers(default_speed - sig, default_speed + sig);
  delay(20);
}

void linetrace_analog(int CNTmax) {
  int CNT = 0;
  while (CNT <= CNTmax) {
    CNT++;
    Serial.print(F("linetrace_analog CNT : "));
    Serial.println(CNT);
    int irData = analogRead(A1);
    // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
    if (irData > irDataMAX) irData = irDataMAX;
    float sig = (irData - threshold) * gain;
    prizm.setMotorPowers(default_speed - sig, default_speed + sig);
    delay(20);
  }
}

void linetrace_analogSetting(float gainData, int default_speedData,
                             int irDataMAXData) {
  gain = gainData;
  default_speed = default_speedData;
  irDataMAX = irDataMAXData;
  threshold = (irDataMAX + 19) / 2 + 1;
  Serial.print(F("LineTrace Setting:"));  // 세팅값 입력
  Serial.println("irDataMAX:" + (String)(irDataMAX) +
                 "  threshold:" + (String)(threshold) + "  default_speed:" +
                 (String)(default_speed) + "  gain:" + (String)(gain));
}

void linetrace_analogSetting(float gainData, int default_speedData,
                             int irDataMAXData, int thresholdData) {
  gain = gainData;
  default_speed = default_speedData;
  irDataMAX = irDataMAXData;
  threshold = thresholdData;
  Serial.print(F("LineTrace Setting:"));  // 세팅값 입력
  Serial.println("irDataMAX:" + (String)(irDataMAX) +
                 "  threshold:" + (String)(threshold) + "  default_speed:" +
                 (String)(default_speed) + "  gain:" + (String)(gain));
}

// count
void intersectionDETECT() {
  if (prizm.readLineSensor(2) == 1) {  // 검정에 닿았을 때
    intersectionCNT++;
    Serial.println("[[[intersectionDETECT]]] intersectionCNT : " +
                   (String)(intersectionCNT));  // digitalDETECT 출력
    GoForward(60, 15);
  }
  delay(20);
}
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
void Get_Avoid_Return(int target_id, int false_id, int return_color) {
  target_object = target_id;
  false_object = false_id;
  return_to = return_color;

  Serial.print(F("Mission Data Receved :: "));
  Serial.print(F("[ Target : "));
  switch (target_object) {
    case COLA:
      Serial.print(F("COLA"));
      servo_maxDEG = 56;
      break;
    case TEA:
      Serial.print(F("TEA"));
      servo_maxDEG = 54;
      break;
    default:
      Serial.print(F("???"));
      break;
  }
  Serial.print(F(" / Avoid : "));
  switch (false_object) {
    case COLA:
      Serial.print(F("COLA"));
      break;
    case TEA:
      Serial.print(F("TEA"));
      break;
    default:
      Serial.print(F("???"));
      break;
  }
  Serial.print(F(" / Return to : "));
  switch (return_color) {
    case GREEN:
      Serial.print(F("GREEN"));
      break;
    case RED:
      Serial.print(F("RED"));
      break;
    case BLUE:
      Serial.print(F("BLUE"));
      break;
    default:
      Serial.print(F("???"));
      break;
  }
  Serial.println(F(" ]"));
}

//****************************** mission func ******************************
void MissionStart() {
  Serial.println(F("Mission Start!!!"));
  move_StartPos();
  check_NODE3();
  NODE_PrintAll();
  canDrop();
  StopFor(1000000);
}

void move_StartPos() {
  move_1node();  // NODE1 으로 이동하기 위해 intersection 2번 이동
  move_1node();
  currentNODE = NODE1;  // 현재 위치 저장
  currnetNEWS = NORTH;  // 현재 방향 저장
  Serial.println(F(">>> At Starting Position"));
  StopFor(100);
}

//****************************** NODE check ******************************
void check_NODE3() {
  GoForward(100, 500);
  Serial.println(F(">>> CHECK FUNC :: check_NODE3"));
  StopFor(0);
  check_1NODE(NODE3);
  // check_1NODE_Far();
  switch (NODE_dataReturn(NODE3)) {
    case 1:
      Serial.println(F("NODE3 1"));
      NODE_movement("2,3,2");
      move_Exit(NODE1);
      break;
    case 2:
      Serial.println(F("NODE3 2"));
      NODE_movement("2,6,7,11,10,9,5");
      move_left();
      GoForward(-60, 800);
      move_Exit(NODE5);
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

void check_NODE59() {
  Serial.println(F(">>> CHECK FUNC :: check_NODE5,9"));
  check_2NODE(NODE5, NODE9);
  int N5 = NODE_dataReturn(NODE5);
  int N9 = NODE_dataReturn(NODE9);
  switch (N5) {
    case 1:
      NODE_movement("5");
      move_right();
      GoForward(-60, 800);
      move_Exit(NODE5);
      break;
    case 2:
      TurnLeft();
      currnetNEWS = NORTH;
      StopFor(200);
      NODE_movement("2,6,7,11,10,9");
      move_Exit(NODE9);
      break;
    case 0:
      switch (N9) {
        case 1:  // ! 문제있음 수정필요
          linetrace_analogSetting(2.0, 40, 40, 35);
          while (prizm.readSonicSensorCM(4) > 15) linetrace_analog();
          canApproach();
          StopFor(500);
          currentNODE = NODE9;  // 현재 위치 저장
          currnetNEWS = EAST;   // 현재 방향 저장
          break;
        case 2:
          TurnLeft();
          currnetNEWS = NORTH;
          StopFor(200);
          NODE_movement("2,3,7,11,10,6,5");
          move_Exit(NODE5);
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

void check_NODE610() {
  Serial.println(F(">>> CHECK FUNC :: check_NODE6,10"));
  check_2NODE(NODE6, NODE10);
  NODE_PrintAll();   // ! 디버그용
  StopFor(1000000);  // ! 디버그용 멈춤
  int N6 = NODE_dataReturn(NODE6);
  int N10 = NODE_dataReturn(NODE10);
  switch (N6) {
    case 1:
      NODE_movement("6,5");
      break;
    case 2:
      TurnLeft();
      currnetNEWS = NORTH;
      NODE_movement("3,7,11,10,9");
      move_Exit(NODE9);
      break;
    case 0:
      switch (N10) {
        case 1:
          NODE_movement("6,10,9");
          break;
        case 2:
          NODE_movement("6,7,11,7,6,5");
          move_Exit(NODE5);
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

void check_NODE7() {
  check_1NODE(NODE7);
  // check_1NODE_Near();
  switch (NODE_dataReturn(NODE7)) {
    case 1:
      NODE_movement("7,6,5");
      move_Exit(NODE5);
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
      move_Exit(NODE9);
      break;
    default:
      break;
  }
}

#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void motorInit() {
  prizm.setMotorInvert(1, 1);
  prizm.setServoSpeed(1, 60);
  prizm.setServoSpeed(2, 60);
  prizm.setServoSpeed(3, 10);

  gripper_openPOS();
}

//****************************** gripper mode ******************************
void gripper_openPOS() {
  prizm.setServoPosition(1, servo1_openPOS);
  prizm.setServoPosition(2, servo2_openPOS);
}

void gripper_closePOS() {
  prizm.setServoPosition(1, servo1_closePOS);
  prizm.setServoPosition(2, servo2_closePOS);
}

void gripper_moveUP(int time) {
  prizm.setServoPosition(1, servo1_closePOS);
  prizm.setServoPosition(2, servo2_closePOS);
  prizm.setServoPosition(3, servo3_upPOS);
  delay(time);
}

//****************************** can grab ******************************
void canGrab() {
  if (!isCanGrab) {
    if (prizm.readSonicSensorCM(4) <= canDetectCm) {
      Serial.println(F("!!!Can Detected!!!"));
      StopFor(50);
      gripper_moveUP(500);
      isCanGrab = true;
      NODE_dataUpdate(currentNODE, 1);
      // if (NODE_dataReturn(NODE11) == 1 || NODE_dataReturn(NODE5) == 1)
      if (NODE_dataReturn(NODE5) == 1) intersectionCNT == 1;
      StopFor(2000);
    }
  }
}

void canApproach() {
  if (!isCanGrab) {
    StopFor(100);
    int SQ_size = ReturnSquareSize();
    if (SQ_size > detectSize) {
      Serial.println(SQ_size);
      Serial.println(F("!!!Can Approach!!!"));
      linetrace_analogSetting(0.7, 10, 40, 35);
      while (!isCanGrab && intersectionCNT == 0) {
        canGrab();
        if (!(NODE_dataReturn(NODE5) == 0 && NODE_dataReturn(NODE9) != 1))
          intersectionDETECT();
        linetrace_analog();
        if (intersectionCNT > 0) break;
      }
      linetrace_analogSetting(3.0, 60, 40, 35);
      linetrace_analog(2);
    } else
      Serial.println(ReturnSquareSize());
  }
}

void canDrop() {
  StopFor(200);
  Serial.println(F("canDrop!!!"));
  gripper_openPOS();
}

//****************************** move mode ******************************
void TurnRight() {
  prizm.setMotorPowers(40, -40);
  delay(750);
  prizm.setMotorPowers(125, 125);  // 정지
  TurnCalib();
}

void TurnLeft() {
  prizm.setMotorPowers(-40, 40);
  delay(750);
  prizm.setMotorPowers(125, 125);  // 정지
  TurnCalib();
}

void TurnAround() {
  prizm.setMotorPowers(100, -100);
  delay(1050);
  prizm.setMotorPowers(125, 125);  // 정지
  TurnCalib();
}

void GoForward(int velocity, int time) {
  prizm.setMotorPowers(velocity, velocity);
  delay(time);
}

void StopFor(unsigned long time) {
  prizm.setMotorPowers(125, 125);  // 정지
  delay(time);
}

void TurnCalib() {
  StopFor(50);
  intersectionDETECT();
  if (intersectionCNT > 0) {
    Serial.println(F("TurnCalib"));
    prizm.setMotorPowers(40, -40);
    delay(50);
    StopFor(50);
  }
  intersectionCNT = 0;
}

//****************************** return home ******************************
void return_from9() {
  if (return_to == GREEN) {
  } else if (return_to == RED) {
  } else if (return_to == BLUE) {
  }
  // can drop
}

void return_from5() {
  if (return_to == GREEN) {
  } else if (return_to == RED) {
  } else if (return_to == BLUE) {
  }
  // can drop
}

void return_from1() {
  if (return_to == GREEN) {
  } else if (return_to == RED) {
  } else if (return_to == BLUE) {
  }
  // can drop
}
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
//****************************** NODE data ******************************
void NODE_to_Arr(int nodeNUM, int& row, int& col) {
  row = nodeNUM / 3;  // 행 위치 계산후 저장
  col = nodeNUM % 3;  // 열 위치 계산후 저장
}

int NODE_dataReturn(int nodeNUM) {
  NODE_to_Arr(nodeNUM, row, col);
  return nodeDataArr[row][col];
}

void NODE_dataPrint(int nodeNUM) {
  NODE_to_Arr(nodeNUM, row, col);
  int nodeNum_data = nodeNumArr[row][col];
  int nodeData_data = nodeDataArr[row][col];
  Serial.print(F("[[NODE"));
  Serial.print(nodeNum_data);
  Serial.print(F(" data : "));
  Serial.print(nodeData_data);
  Serial.println(F(" ]]"));
}

void NODE_dataUpdate(int nodeNUM, int data) {
  NODE_to_Arr(nodeNUM, row, col);
  nodeDataArr[row][col] = data;
  NODE_dataPrint(nodeNUM);
}

int NODE_convert(int node_num) {
  switch (node_num) {
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
      return 0;  // Added default return value
  }
}

void NODE_PrintAll() {
  Serial.println(F("\nNODE DATA PRINT"));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      String node_data = String(nodeDataArr[i][j]);
      if (node_data == "7") node_data = "?";
      Serial.print(node_data);
      if (j < 2) Serial.print(F(" . "));
    }
    Serial.println("");
  }
}

//****************************** NODE move ******************************
void NODE_move(int to) { NODE_move(currentNODE, to); }

void NODE_move(int from, int to) {
  NODE_to_Arr(from, row, col);
  int from_row = row;
  int from_col = col;
  NODE_to_Arr(to, row, col);
  int to_row = row;
  int to_col = col;
  int row_move = from_row - to_row;
  int col_move = to_col - from_col;
  Serial.print(F("NODE_move / from:"));
  Serial.print(from_row);
  Serial.print(F(","));
  Serial.print(from_col);
  Serial.print(F(" / to:"));
  Serial.print(to_row);
  Serial.print(F(","));
  Serial.print(to_col);
  Serial.print(F(" / "));
  Serial.println(row_move * 10 + col_move);
  currentNODE = to;
  switch (row_move * 10 + col_move) {
    case 00:
      Serial.println(F("move : stay"));
      break;
    case 01:
      Serial.println(F("move : EAST"));
      move_NEWS(EAST);
      break;
    case -01:
      Serial.println(F("move : WEST"));
      move_NEWS(WEST);
      break;
    case 10:
      Serial.println(F("move : NORTH"));
      move_NEWS(NORTH);
      break;
    case -10:
      Serial.println(F("move : SOUTH"));
      move_NEWS(SOUTH);
      break;
    default:
      StopFor(100000);
      break;
  }
}

void move_NEWS(int news) {
  switch (news - currnetNEWS) {
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
  Serial.println(F("move_1node"));
  move_1node();
}

//****************************** NODE movement ******************************
void NODE_movement(String input) {
  Serial.print(F("[[ NODE_movement : "));
  Serial.print(input);
  Serial.println(F(" ]]"));
  movement_parsing(input);
  int movetotalCNT = moveCNT;
  while (moveCNT > 0) {
    Serial.print(F("moveCNT:"));
    Serial.println(moveCNT);
    int moveto = moveArr[movetotalCNT - moveCNT];
    NODE_move(NODE_convert(moveto));
    moveCNT--;
  }
  for (int i = 0; i < 15; i++) moveArr[i] = 0;
}

void movement_parsing(String input) {
  int index = 0;                 // 배열 인덱스 초기화
  int pos = input.indexOf(',');  // 쉼표로 구분된 숫자 추출
  while (pos != -1 && moveCNT < 15) {
    moveArr[moveCNT++] =
        input.substring(index, pos).toInt();  // 숫자로 변환하여 저장
    index = pos + 1;
    pos = input.indexOf(',', index);  // 다음 쉼표 위치 찾기
  }

  if (moveCNT < 15)  // 마지막 숫자 처리
    moveArr[moveCNT++] = input.substring(index).toInt();

  for (int i = moveCNT; i < 15; i++)  // 배열 나머지 부분을 0으로 채우기
    moveArr[i] = 0;
}

//****************************** move 1node ******************************
void move_1node() {
  while (intersectionCNT < 1) {
    intersectionDETECT();
    linetrace_analog();
  }
  intersectionCNT = 0;
}

void move_little(int maxCNT) {
  int CNT = 0;
  while (CNT < maxCNT) {
    linetrace_analog();
    CNT++;
  }
  StopFor(100);
}

//****************************** simple move ******************************
void move_right() {
  StopFor(200);
  GoForward(60, 450);
  TurnRight();
  StopFor(700);
}

void move_left() {
  StopFor(200);
  GoForward(60, 380);
  TurnLeft();
  StopFor(700);
}

void move_180() {
  StopFor(200);
  GoForward(60, 400);
  TurnAround();
  StopFor(700);
}

//****************************** return home ******************************
void move_Exit(int exitNode) {
  StopFor(500);
  switch (exitNode) {
    case NODE5:
      switch (return_to) {
        case GREEN:
          prizm.setMotorPowers(40, -40);
          delay(180);
          StopFor(500);
          GoForward(60, 1800);
          break;
        case RED:
          GoForward(60, 2000);
          break;
        case BLUE:
          prizm.setMotorPowers(-40, 40);
          delay(180);
          StopFor(500);
          GoForward(60, 1800);
          break;
        default:
          break;
      }
      break;
    case NODE9:
      switch (return_to) {
        case GREEN:
          prizm.setMotorPowers(40, -40);
          delay(370);
          StopFor(500);
          GoForward(60, 2500);
          break;
        case RED:
          prizm.setMotorPowers(40, -40);
          delay(300);
          StopFor(500);
          GoForward(60, 1900);
          break;
        case BLUE:
          GoForward(60, 2000);
          break;
        default:
          break;
      }
      break;
    case NODE1:
      switch (return_to) {
        case GREEN:
          break;
        case RED:
          GoForward(40, 1200);
          StopFor(500);
          prizm.setMotorPowers(-40, 40);
          delay(700);
          StopFor(0);
          GoForward(60, 500);
          break;
        case BLUE:
          GoForward(40, 1200);
          StopFor(500);
          prizm.setMotorPowers(-40, 40);
          delay(700);
          StopFor(0);
          GoForward(60, 1200);
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
