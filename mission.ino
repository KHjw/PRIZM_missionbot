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

//****************************** initial movement ******************************
void move_StartBoost(){
  GoForward(80, 700);
  ptrCurrentMode = move_StartPos;
}

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
    NODE_movement("5");
  }
}

//****************************** mission func ******************************
void check_NODE3(){
  StopFor(0);
  check_1NODE_72();
  switch (NODE_dataReturn(NODE1)){
  case 1:
    // exit 0 (2,3,2)
    break;
  case 2:
    // exit new5 (2,6,7,11,10,9,5)
    break;
  case 0:
    break;
  default:
    break;
  }
}

void check_NODE59(){
  move_right();
  StopFor(0);
  check_2NODE(NODE5, NODE9);
  int N5 = NODE_dataReturn(NODE5);
  int N9 = NODE_dataReturn(NODE9);
  switch(N5){
  case 1:
    // exit new5 (5)
    break;
  case 2:
    // exit 9 (2,6,7,11,10,9)
    break;
  case 0:
    switch (N9){
    case 1:
      // exit new9 (5,9)
      break;
    case 2:
      // exit 5 (2,3,7,11,10,6,5)
      break;
    case 0:
      // check_NODE610()
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
  // (2)
  move_right();
  StopFor(0);
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
  check_1NODE_15();
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