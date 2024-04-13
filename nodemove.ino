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