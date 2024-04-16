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
