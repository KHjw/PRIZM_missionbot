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
  check_1NODE_Far();
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
  check_1NODE_Near();
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
