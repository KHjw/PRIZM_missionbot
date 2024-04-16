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
  Serial.print(F(" ]]"));
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
  int index = 0;  // 배열 인덱스 초기화

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
    case NODE5_v2:
      break;
    case NODE9_v2:
      break;
    default:
      break;
  }
}