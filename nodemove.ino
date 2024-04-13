//****************************** NODE data ******************************
void NODE_to_Arr(int nodeNUM, int& row, int& col){
  row = nodeNUM / 3;  // 행 위치 계산후 저장
  col = nodeNUM % 3;  // 열 위치 계산후 저장
}

int NODE_dataReturn(int nodeNUM){
  NODE_to_Arr(nodeNUM, row, col);
  return nodeDataArr[row][col];
}

void NODE_dataPrint(int nodeNUM){
  NODE_to_Arr(nodeNUM, row, col);
  int nodeNum_data = nodeNumArr[row][col];
  int nodeData_data = nodeDataArr[row][col];
  Serial.print("[[NODE"+(String)(nodeNum_data));
  Serial.println(" data : "+(String)(nodeData_data)+" ]]");
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

void NODE_PrintAll(){
  Serial.println("\nNODE DATA PRINT");
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      String node_data = (String)(nodeDataArr[i][j]);
      if(node_data == "7") node_data = "?";
      Serial.print(node_data);
      if(j<2) Serial.print(" . ");
    }
    Serial.println("");
  }
}

//****************************** NODE move ******************************
void NODE_move(int to){
  NODE_move(currentNODE, to);
}

void NODE_move(int from, int to){
  // 행렬 정보 임시 저장
  NODE_to_Arr(from, row, col);
  int from_row = row;
  int from_col = col;
  NODE_to_Arr(to, row, col);
  int to_row = row;
  int to_col = col;
  // 행렬 움직임 계산
  int row_move = from_row-to_row;
  int col_move = to_col-from_col;
  // 디버깅용 정보 출력
  Serial.print("NODE_move / ");
  Serial.print("from:"+(String)(from_row)+","+(String)(from_col)+" / ");
  Serial.print("to:"+(String)(to_row)+","+(String)(to_col)+" / ");
  Serial.println(row_move*10 + col_move);
  // 현재 위치를 도착지로 갱신
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
}

void NODE_movementGrab(String input){

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
  StopFor(200);
  GoForward(60, 450);
  TurnRignt();
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