void Get_Avoid_Return(int target_id, int false_id, int return_color) {
  target_object = target_id;
  false_object = false_id;
  return_to = return_color;

  Serial.print(F("Mission Data Receved :: "));
  Serial.print(F("[ Target : "));
  switch (target_object) {
    case COLA:
      Serial.print(F("COLA"));
      servo_maxDEG = 58;
      canDetectCm = 3;
      break;
    case TEA:
      Serial.print(F("TEA"));
      servo_maxDEG = 54;
      canDetectCm = 2;
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
  canDrop();
  NODE_PrintAll();
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

void MissionStart_register() {
  while (1) {
    int SQ_size = ReturnSquareSize();
    int registerId = IdReturn();
    if (SQ_size > 20000 && registerId != 0) {
      if (registerId == COLA)
        Get_Avoid_Return(COLA, TEA, return_to);
      else
        Get_Avoid_Return(TEA, COLA, return_to);
      break;
    }
  }
  gripper_closePOS();
  StopFor(300);
  gripper_openPOS();
  StopFor(3000);
  MissionStart();
}

void Mission_Stupid() {
  isStupidMode = true;
  Serial.println(F("Stupid Mission Start!!!"));
  move_StartPos();
  // ? 이동
  NODE_movement("2,3,7,11");
  // ! 탈출
  move_180();
  prizm.setMotorPowers(100, -100);
  delay(100);
  currnetNEWS = WEST;
  linetrace_analog(35);
  TurnLeft();
  currentNODE = NODE7;  // 현재 위치 저장
  currnetNEWS = SOUTH;
  NODE_movement("6,5");
  // ? 도착
  canDrop();
  NODE_PrintAll();
  StopFor(1000000);
}

//****************************** NODE check ******************************
void check_NODE3() {
  GoForward(100, 500);
  Serial.println(F(">>> CHECK FUNC :: check_NODE3"));
  StopFor(0);
  check_1NODE(NODE3);
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
        case 1:
          StopFor(1000);
          while (prizm.readSonicSensorCM(4) > 15) linetrace_analog();
          currentNODE = NODE9;  // 현재 위치 저장
          currnetNEWS = EAST;   // 현재 방향 저장
          canApproach();
          move_right();
          GoForward(-60, 800);
          move_Exit(NODE9);
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
      move_1node();
      currentNODE = NODE6;  // 현재 위치 저장
      currnetNEWS = EAST;   // 현재 방향 저장
      switch (N10) {
        case 1:
          NODE_movement("10,9");
          move_Exit(NODE9);
          break;
        case 2:
          move_left();
          currnetNEWS = NORTH;
          check_1NODE(NODE7);
          if (NODE_dataReturn(NODE7) == 1)
            NODE_movement("7,6,5");
          else {
            NODE_movement("7,11");
            move_180();
            prizm.setMotorPowers(100, -100);
            delay(100);
            currnetNEWS = WEST;
            linetrace_analog(35);
            TurnLeft();
            currentNODE = NODE7;  // 현재 위치 저장
            currnetNEWS = SOUTH;
            NODE_movement("6,5");
          }
          move_Exit(NODE5);
          break;
        case 0:
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
  switch (NODE_dataReturn(NODE7)) {
    case 1:
      NODE_movement("7,6,5");
      move_Exit(NODE5);
      break;
    case 2:
      GoForward(-40, 50);
      TurnRight();
      currnetNEWS = EAST;
      NODE_movement("10");
      move_left();
      currentNODE = NODE11;
      currnetNEWS = NORTH;
      canApproach();
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
