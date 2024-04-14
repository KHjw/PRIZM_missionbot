void huskeylensInit(){
  Wire.begin();
  while(!huskylens.begin(Wire)){
    Serial.println(F("Begin failed!"));
    delay(100);
  }
}

void check_1NODE_Far(){
  int sonic_data = 0;
  int checkNUM = 3;
  for(int i = 0; i < checkNUM; i++){
    sonic_data += prizm.readSonicSensorCM(4);
    delay(100);
  } 
  sonic_data = sonic_data / checkNUM;
  Serial.print(F("sonic data : "));
  Serial.println(sonic_data);
  if(48 < sonic_data && sonic_data <= 58){
    if(isObjectTarget())  NODE_dataUpdate(NODE3, 1);
    else                  NODE_dataUpdate(NODE3, 2);
  }
  else
    NODE_dataUpdate(NODE3, 0);
}

void check_1NODE_Near(){
  int sonic_data = 0;
  int checkNUM = 3;
  for(int i = 0; i < checkNUM; i++){
    sonic_data += prizm.readSonicSensorCM(4);
    delay(100);
  } 
  sonic_data = sonic_data / checkNUM;
  Serial.print(F("sonic data : "));
  Serial.println(sonic_data);
  if(3 < sonic_data && sonic_data <= 15){
    if(isObjectTarget())  NODE_dataUpdate(NODE7, 1);
    else                  NODE_dataUpdate(NODE7, 2);
  }
  else
    NODE_dataUpdate(NODE7, 0);
}

void check_2NODE(int node_near, int node_far){
  int sonic_data = 0;
  int checkNUM = 3;
  for(int i = 0; i < checkNUM; i++){
    sonic_data += prizm.readSonicSensorCM(4);
    delay(100);
  } 
  sonic_data = sonic_data / checkNUM;
  Serial.print(F("sonic data : "));
  Serial.println(sonic_data);
  if(11 < sonic_data && sonic_data <= 19){
    if(isObjectTarget())  NODE_dataUpdate(node_near, 1);
    else                  NODE_dataUpdate(node_near, 2);
  }
  else if(50 < sonic_data && sonic_data <= 60){
    NODE_dataUpdate(node_near, 0);
    if(isObjectTarget())  NODE_dataUpdate(node_far, 1);
    else                  NODE_dataUpdate(node_far, 2);
  }
  else{
    NODE_dataUpdate(node_near, 0);
    NODE_dataUpdate(node_far, 0);
  }
  ptrCurrentMode = NODE_PrintAll;
}

bool isObjectTarget(){
  int id_detected = 0;
  while(id_detected == 0){
    if(ReturnObjectCNT() < 2){
      Serial.print(F("Object CNT == 1 / "));
      id_detected = IdReturn();
    }
    else{
      Serial.print(F("Object CNT >= 2 / "));
      id_detected = IdReturn_Closer();
    }
  }
  Serial.print(F("detected id : "));
  Serial.println(id_detected);
  if(id_detected == target_object)  return true;
  else return false;
}

int ReturnSquareSize(){
  int zeroCount = 0;  // 인식된 객체가 없는 상황을 카운트하는 변수

  while (true) {
    if (!huskylens.request() || !huskylens.isLearned() || !huskylens.available()) {
      zeroCount++;  // 조건에 맞지 않는 경우 카운트 증가
      if (zeroCount >= 3)
        return 0;  // 3회 연속으로 객체가 인식되지 않은 경우 0을 반환
      continue;  // 조건에 맞지 않으면 계속 반복
    }
    int maxSquare = 0;  // 최대 크기 저장 변수 초기화
    zeroCount = 0;  // 인식된 객체가 있으므로 카운터를 리셋
    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      int currentSquare = result.width * result.height;  // 현재 객체의 크기 계산
      if (currentSquare > maxSquare)    // 현재 객체가 지금까지 발견된 가장 큰 객체보다 크면
        maxSquare = currentSquare;      // 최대 크기를 현재 객체 크기로 업데이트
    }
    if (maxSquare > 0)  
      return maxSquare;  // 가장 큰 객체의 크기 반환
  }
}


int IdReturn(){
  if (!huskylens.request())
    return 0;
  else if (!huskylens.isLearned())
    return 0;
  else if (!huskylens.available())
    return 0;
  else{
    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      if (result.command == COMMAND_RETURN_BLOCK) {
        if (result.ID == 1 || result.ID == 2 || result.ID == 3) {
          Serial.print(F("Block ID="));
          Serial.println(result.ID);
          return result.ID;
        }
      }
    }
  }
  return 0; // 반환할 객체 ID가 없으면 0을 반환
}

int IdReturn_Closer(){
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
