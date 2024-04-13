void Get_Avoid_Return(int target_id, int false_id, int return_color){
  target_object = target_id;
  false_object = false_id;
  return_to = return_color;

  Serial.print("Mission Data Receved :: ");
  Serial.print("[ Target : ");
  switch (target_object){
  case COLA:
    Serial.print("COLA");
    break;
  case MONSTER:
    Serial.print("MONSTER");
    break;
  case TEA:
    Serial.print("TEA");
    break;
  default:
    Serial.print("???");
    break;
  }
  Serial.print(" / Avoid : ");
  switch (false_object){
  case COLA:
    Serial.print("COLA");
    break;
  case MONSTER:
    Serial.print("MONSTER");
    break;
  case TEA:
    Serial.print("TEA");
    break;
  default:
    Serial.print("???");
    break;
  }
  Serial.print(" / Return to : ");
  switch (false_object){
  case GREEN:
    Serial.print("GREEN");
    break;
  case RED:
    Serial.print("RED");
    break;
  case BLUE:
    Serial.print("BLUE");
    break;
  default:
    Serial.print("???");
    break;
  }
  Serial.println(" ]");
}

//****************************** mission func ******************************
void MissionStart(){
  Serial.println("Mission Start!!!");
  move_StartPos();
  check_NODE3();
  NODE_PrintAll();
  StopFor(1000000);
}

void move_StartPos(){
  GoForward(80, 700);       // 첫 번째 intersection 지날때 까지 boost
  move_1node();             // NODE1 으로 이동
  currentNODE = NODE1;      // 현재 위치 저장
  currnetNEWS = NORTH;      // 현재 방향 저장
  Serial.println(">>> At Starting Position");
  StopFor(100);
}

void check_NODE3(){
  GoForward(100, 500);
  Serial.println(">>> CHECK FUNC :: check_NODE3");
  StopFor(0);
  check_1NODE_Far();
  switch (NODE_dataReturn(NODE1)){
  case 1:
    // exit 0 (2,3,2)
    break;
  case 2:
    // exit new5 (2,6,7,11,10,9,5)
    break;
  case 0:
    TurnRignt();
    currnetNEWS = EAST;
    StopFor(200);
    check_NODE59();
    break;
  default:
    break;
  }
}

void check_NODE59(){
  Serial.println(">>> CHECK FUNC :: check_NODE5,9");
  check_2NODE(NODE5, NODE9);
  int N5 = NODE_dataReturn(NODE5);
  int N9 = NODE_dataReturn(NODE9);
  switch(N5){
  case 1:
    // exit new5 (5)
    break;
  case 2:
    TurnLeft();
    currnetNEWS = NORTH;
    StopFor(200);
    NODE_movement("2,6,7,11,10,9");
    break;
  case 0:
    switch (N9){
    case 1:
      // exit new9 (5,9)
      break;
    case 2:
      TurnLeft();
      currnetNEWS = NORTH;
      StopFor(200);
      NODE_movement("2,3,7,11,10,6,5");
      // exit 5 (2,3,7,11,10,6,5)
      break;
    case 0:
      // (2)
      // move_right();
      // StopFor(0);
      // check_NODE610();
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
  Serial.println(">>> CHECK FUNC :: check_NODE6,10");
  check_2NODE(NODE6, NODE10);
  int N6 = NODE_dataReturn(NODE6);
  int N10 = NODE_dataReturn(NODE10);
  switch(N6){
  case 1:
    // exit 5 (2,6,5)
    break;
  case 2:
    // exit 9 (2,3,7,11,10,9)
    break;
  case 0:
    switch (N10){
    case 1:
      // exit 9 (2,6,10,9)
      break;
    case 2:
      // 체크
      break;
    case 0:
      // check_NODE7()
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
    // exit 5 (7,6,5)
    break;
  case 2:
    // exit 9 (10,11,10,9)
    break;
  default:
    break;
  }
}