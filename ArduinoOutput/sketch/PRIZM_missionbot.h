#line 1 "/Users/kh_jinu/Desktop/응용로봇공/PRIZM_missionbot/PRIZM_missionbot.h"
#ifndef _DONE_EMLOCK_CODE_
#define _DONE_EMLOCK_CODE_

#include <PRIZM.h>
#include <stdlib.h>
#include <string.h>

#include "HUSKYLENS.h"

//****************************** system SETUP ******************************
bool tf = false;

int target_object = 0;
int false_object = 0;
int return_to = 0;

#define detectSize 500

PRIZM prizm;

void (*ptrCurrentMode)();  // 현재모드 함수 포인터
void (*ptrCheckMode)();    // 확인 함수 포인터

// battry
int battVoltage = 0;
void battVoltagePrint();
void battVoltagePrint(int time);
void setBattVoltage2(float setVoltage);

void voidFunc() {}

//****************************** motor SETUP ******************************
void motorInit();

// gripper 초기 각도 설정
#define servo1_openPOS 110  // servo1 열렸을때의 각도
#define servo2_openPOS 35   // servo2 열렸을때의 각도
#define servo3_downPOS 90   // servo3 내려갔을때의 각도

int servo_maxDEG = 54;
int servo1_closePOS = servo1_openPOS - servo_maxDEG;  // servo1 닫혔을때의 각도
int servo2_closePOS = servo2_openPOS + servo_maxDEG;  // servo2 닫혔을때의 각도
#define servo3_upPOS 50  // servo3 올라갔을때의 각도

// gripper
int canDetectCm = 3;
#define canApproachCm 15

bool isCanGrab = false;
void gripper_openPOS();
void gripper_closePOS();
void gripper_moveUP(int time);  // 들어올리는데 걸리는 시간
void canGrab();

// move
void TurnRight();
void TurnLeft();
void GoForward(int velocity, int time);
void StopFor(unsigned long time);

//****************************** nodemove SETUP ******************************
enum { NORTH = 0, EAST, SOUTH, WEST };
enum {
  NODE3 = 0,
  NODE7,
  NODE11,
  NODE2,
  NODE6,
  NODE10,
  NODE1,
  NODE5,
  NODE9,
  NODE5_v2,
  NODE9_v2
};

int currentNODE = 0;  // current NODE
int currnetNEWS = 0;  // current DIRECTION(N,E,W,S)
int moveCNT = 0;      // 숫자 카운트 초기화
int moveArr[15] = {0};

int nodeNumArr[3][3] = {{3, 7, 11}, {2, 6, 10}, {1, 5, 9}};

int nodeDataArr[3][3] = {{7, 7, 7}, {0, 7, 7}, {0, 7, 7}};

int row = 0, col = 0;
void NODE_to_Arr(int nodeNUM, int& row, int& col);

void NODE_dataPrint(int nodeNUM);
void NODE_dataUpdate(int nodeNUM, int data);

void NODE_move(int to);
void NODE_move(int from, int to);
void NODE_movement(String input);

void move_1node();

//****************************** linetrace SETUP ******************************
int irDataMAX = 26;
float gain = 1.45;
int default_speed = 10;
int threshold = (irDataMAX + 19) / 2 + 1;
int testCNT = 0;

void linetrace_analogPrint(int time);
void linetrace_analog();
void linetrace_analogSetting(float gainData, int default_speedData,
                             int irDataMAXData);
void linetrace_analogSetting(float gainData, int default_speedData,
                             int irDataMAXData, int thresholdData);

int intersectionCNT = 0;
void intersectionDETECT();

//****************************** huskylens SETUP ******************************
HUSKYLENS huskylens;

enum { COLA = 3, TEA = 2 };
enum { GREEN = 1, RED, BLUE };

//****************************** mission SETUP ******************************

#endif