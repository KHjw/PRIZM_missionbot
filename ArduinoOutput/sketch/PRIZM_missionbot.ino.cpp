#include <Arduino.h>
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino"
#include "PRIZM_missionbot.h"

//========================== main func ==========================
#line 4 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino"
void setup();
#line 16 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino"
void loop();
#line 2 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/battry.ino"
void battVoltagePrint();
#line 7 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/battry.ino"
void battVoltagePrint(int time);
#line 13 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/battry.ino"
void setBattVoltage2(float setVoltage);
#line 2 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
void linetrace_digitalPrint(int time);
#line 12 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
void linetrace_digital();
#line 25 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
void linetrace_analogPrint(int time);
#line 40 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
void linetrace_analog();
#line 52 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
void linetrace_analogSetting(float gainData, int default_speedData, int irDataMAXData);
#line 61 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
void linetrace_analogSetting(float gainData, int default_speedData, int irDataMAXData, int thresholdData);
#line 71 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
void intersectionDETECT();
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
void T_method(int target, int trap, int returnto);
#line 5 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
void Snail_method(int target, int trap, int returnto);
#line 9 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
void StartMission();
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void motorInit();
#line 12 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void gripper_openPOS();
#line 17 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void gripper_closePOS();
#line 22 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void gripper_moveUP(int time);
#line 29 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void canGrab();
#line 41 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void TurnRignt();
#line 48 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void TurnLeft();
#line 55 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void TurnAround();
#line 62 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void GoForward(int velocity, int time);
#line 68 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void StopFor(long time);
#line 73 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
void Wait();
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void move_StartPos();
#line 16 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void move_StartBoost();
#line 23 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void NODE_to_Arr(int nodeNUM, int& row, int& col);
#line 28 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void NODE_dataPrint(int nodeNUM);
#line 36 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void NODE_dataUpdate(int nodeNUM, int data);
#line 44 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
int NODE_convert(int node_num);
#line 79 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void NODE_move(int to);
#line 83 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void NODE_move(int from, int to);
#line 128 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void move_NEWS(int news);
#line 151 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void NODE_movement(String input);
#line 165 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void movement_parsing(String input);
#line 183 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void move_1node();
#line 191 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void move_right();
#line 197 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void move_left();
#line 203 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void move_180();
#line 4 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.ino"
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
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/battry.ino"
// robot State Check
void battVoltagePrint(){
  int battVoltage = prizm.readBatteryVoltage();
  Serial.println("battVoltage : "+(String)(battVoltage/100)+"."+(String)(battVoltage%100)+"V");   // 현 배터리 전압 체크
}

void battVoltagePrint(int time){
  int battVoltage = prizm.readBatteryVoltage();
  Serial.println("battVoltage : "+(String)(battVoltage/100)+"."+(String)(battVoltage%100)+"V");   // 현 배터리 전압 체크
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
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/huskylens.ino"

#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/linetrace.ino"
//******************************DIGITAL Linetrace******************************
void linetrace_digitalPrint(int time){
  if(prizm.readLineSensor(2) == 1){   // 검정에 닿았을 때
    Serial.println("1");              // . 출력
  }
  else{                               // 흰색에 닿았을 때
    Serial.print(".");                // 1 출력
  }
  delay(time);
}

void linetrace_digital(){
  if(prizm.readLineSensor(2) == 0){   // 흰색에 닿았을 때
    Serial.print(".");                // . 출력
    prizm.setMotorPowers(10,125);
  }
  else{                               // 검정색에 닿았을 때
    Serial.println("1");              // 1 출력
    prizm.setMotorPowers(125,10);
  }
  delay(100);
}

//******************************ANALOG Linetrace******************************
void linetrace_analogPrint(int time){
  int irData = analogRead(A1); 
  if(irData > irDataMAX){       // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
    irData = irDataMAX;
    Serial.print("irData calib -> "); 
  }
  Serial.print((String)(irData)+". ");
  if(testCNT > 10){
    Serial.print("\n");
    testCNT = 0;
  }
  testCNT ++;
  delay(time);
}

void linetrace_analog(){
  int irData = analogRead(A1); 
  if(irData > irDataMAX){       // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
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
  Serial.println("\nLineTrace Setting:");         // 세팅값 입력
  Serial.println("irDataMAX:"+(String)(irDataMAX)+"  threshold:"+(String)(threshold)+"  default_speed:"+(String)(default_speed)+"  gain:"+(String)(gain));
}

void linetrace_analogSetting(float gainData, int default_speedData, int irDataMAXData, int thresholdData){
  gain = gainData;
  default_speed = default_speedData;
  irDataMAX = irDataMAXData;
  threshold = thresholdData;
  Serial.println("\nLineTrace Setting:");         // 세팅값 입력
  Serial.println("irDataMAX:"+(String)(irDataMAX)+"  threshold:"+(String)(threshold)+"  default_speed:"+(String)(default_speed)+"  gain:"+(String)(gain));
}

// count
void intersectionDETECT(){
  if(prizm.readLineSensor(2) == 1){   // 검정에 닿았을 때
    intersectionCNT++;
    Serial.print("\n\n[[[intersectionDETECT]]] intersectionCNT : " + (String)(intersectionCNT)+"\n\n");    // digitalDETECT 출력
    GoForward(60, 15);
  }
  delay(20);
}
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/mission.ino"
void T_method(int target, int trap, int returnto){

}

void Snail_method(int target, int trap, int returnto){

}

void StartMission(){
  
}
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/motor.ino"
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

void canGrab(){
  if(!isCanGrab){
    if(prizm.readSonicSensorCM(4) <= canDetectCm){
      prizm.setMotorPowers(125,125);  // 정지
      Serial.println("Can Detected!!!");
      gripper_moveUP(2000);
      isCanGrab = true;
    }
  }
}

//****************************** move mode ******************************
void TurnRignt(){
  Serial.println("TurnRignt");
  prizm.setMotorPowers(40, -40);
  delay(750);
  prizm.setMotorPowers(125, 125);   // 정지
}

void TurnLeft(){
  Serial.println("TurnLeft");
  prizm.setMotorPowers(-40, 40);
  delay(750);
  prizm.setMotorPowers(125, 125);   // 정지
}

void TurnAround(){
  Serial.println("TurnAround");
  prizm.setMotorPowers(100, -100);
  delay(1050);
  prizm.setMotorPowers(125, 125);   // 정지
}

void GoForward(int velocity, int time){
  Serial.println("GoForward");
  prizm.setMotorPowers(velocity, velocity);
  delay(time);
}

void StopFor(long time){
  prizm.setMotorPowers(125, 125);   // 정지
  delay(time);
}

void Wait(){
  prizm.setMotorPowers(125, 125);   // 정지
  ptrCurrentMode = voidFunc;
}
#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/nodemove.ino"
void move_StartPos(){
  intersectionDETECT();
  if(intersectionCNT < 1){
    Serial.print(".");
    linetrace_analog();
  }
  else{
    currentNODE = NODE1;
    currnetNEWS = NORTH;
    intersectionCNT = 0;
    NODE_movement("2,3,7,11,10,6,5");
    // ptrCurrentMode = Wait;
  }
}

void move_StartBoost(){
  GoForward(80, 700);
  // StopFor(1000000);
  ptrCurrentMode = move_StartPos;
}

//****************************** NODE data ******************************
void NODE_to_Arr(int nodeNUM, int& row, int& col){
  row = nodeNUM / 3;  // 행 위치 계산후 저장
  col = nodeNUM % 3;  // 열 위치 계산후 저장
}

void NODE_dataPrint(int nodeNUM){
  NODE_to_Arr(nodeNUM, row, col);
  int nodeNum_data = nodeNumArr[row][col];
  int nodeData_data = nodeDataArr[row][col];
  Serial.print("[[NODE"+(String)(nodeNum_data));
  Serial.println(" data : "+(String)(nodeData_data)+" ]]");
}

void NODE_dataUpdate(int nodeNUM, int data){
  Serial.print("NODE data updating...");
  NODE_to_Arr(nodeNUM, row, col);
  nodeDataArr[row][col] = data;
  Serial.println("   complete");
  NODE_dataPrint(nodeNUM);
}

int NODE_convert(int node_num){
  switch (node_num){
  case 1:
    return NODE1;
    break;
  case 2:
    return NODE2;
    break;
  case 3:
    return NODE3;
    break;
  case 5:
    return NODE5;
    break;
  case 6:
    return NODE6;
    break;
  case 7:
    return NODE7;
    break;
  case 9:
    return NODE9;
    break;
  case 10:
    return NODE10;
    break;
  case 11:
    return NODE11;
    break;
  default:
    break;
  }
}

//****************************** NODE move ******************************
void NODE_move(int to){
  NODE_move(currentNODE, to);
}

void NODE_move(int from, int to){
  Serial.print("NODE_move / ");
  int from_row = 0, from_col = 0, to_row = 0, to_col = 0;

  NODE_to_Arr(from, row, col);
  from_row = row;
  from_col = col;
  Serial.print("from:"+(String)(from_row)+","+(String)(from_col)+" / ");
  NODE_to_Arr(to, row, col);
  to_row = row;
  to_col = col;
  Serial.print("to:"+(String)(to_row)+","+(String)(to_col)+" / ");

  int row_move = from_row-to_row;
  int col_move = to_col-from_col;
  Serial.println(row_move*10 + col_move);
  
  currentNODE = to;
  switch(row_move*10 + col_move){
    case 00:
      Serial.println("move : stay");
      StopFor(100000);
      break;
    case 01:
      Serial.println("move : EAST");
      move_NEWS(EAST);
      break;
    case -01:
      Serial.println("move : WEST");
      move_NEWS(WEST);
      break;
    case 10:
      Serial.println("move : NORTH");
      move_NEWS(NORTH);
      break;
    case -10:
      Serial.println("move : SOUTH");
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
  Serial.println("move_1node");
  move_1node();
}

//****************************** NODE movement ******************************
void NODE_movement(String input){
  movement_parsing(input);
  int movetotalCNT = moveCNT;
  while(moveCNT > 0){
    Serial.println("moveCNT:"+(String)(moveCNT));
    int moveto = moveArr[movetotalCNT - moveCNT];
    NODE_move(NODE_convert(moveto));
    moveCNT--;
  }
  for (int i = 0; i < 15; i++)
    moveArr[i] = 0;
  ptrCurrentMode = Wait;
}

void movement_parsing(String input){
  int index = 0;  // 배열 인덱스 초기화

  int pos = input.indexOf(',');  // 쉼표로 구분된 숫자 추출  
  while (pos != -1 && moveCNT < 15) {
    moveArr[moveCNT++] = input.substring(index, pos).toInt(); // 숫자로 변환하여 저장
    index = pos + 1;
    pos = input.indexOf(',', index); // 다음 쉼표 위치 찾기
  }
  
  if (moveCNT < 15)  // 마지막 숫자 처리
    moveArr[moveCNT++] = input.substring(index).toInt();

  for (int i = moveCNT; i < 15; i++)  // 배열 나머지 부분을 0으로 채우기
    moveArr[i] = 0;
}

//****************************** simple move ******************************
void move_1node(){
  while(intersectionCNT < 1){
    intersectionDETECT();
    linetrace_analog();
  }
  intersectionCNT = 0;
}

void move_right(){
  GoForward(60, 450);
  TurnRignt();
  StopFor(700);
}

void move_left(){
  GoForward(60, 300);
  TurnLeft();
  StopFor(700);
}

void move_180(){
  GoForward(60, 400);
  TurnAround();
  StopFor(700);
}
