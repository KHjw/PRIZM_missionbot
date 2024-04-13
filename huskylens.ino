void huskeylensInit(){
  Wire.begin();
  while(!huskylens.begin(Wire)){
    Serial.println(F("Begin failed!"));
    delay(100);
  }
}

void check_1NODE_72(){
  int sonic_data = 0;
  int checkNUM = 3;
  for(int i=0; i<checkNUM; i++){
    sonic_data += prizm.readSonicSensorCM(4);
    delay(100);
  } 
  sonic_data = sonic_data/checkNUM;
  Serial.print("sonic data : "+(String)(sonic_data)+" / ");
  if(66 < sonic_data && sonic_data <= 80){
    if(isObjectTarget())  NODE_dataUpdate(NODE3, 1);
    else                  NODE_dataUpdate(NODE3, 2);
  }
  else
    NODE_dataUpdate(NODE3, 0);
}

void check_1NODE_15(){
  int sonic_data = 0;
  int checkNUM = 3;
  for(int i=0; i<checkNUM; i++){
    sonic_data += prizm.readSonicSensorCM(4);
    delay(100);
  } 
  sonic_data = sonic_data/checkNUM;
  Serial.print("sonic data : "+(String)(sonic_data)+" / ");
  if(11 < sonic_data && sonic_data <= 19){
    if(isObjectTarget())  NODE_dataUpdate(NODE7, 1);
    else                  NODE_dataUpdate(NODE7, 2);
  }
  else
    NODE_dataUpdate(NODE3, 0);
}

void check_2NODE(int node_near, int node_far){
  int sonic_data = 0;
  int checkNUM = 3;
  for(int i=0; i<checkNUM; i++){
    sonic_data += prizm.readSonicSensorCM(4);
    delay(100);
  } 
  sonic_data = sonic_data/checkNUM;
  Serial.print("sonic data : "+(String)(sonic_data)+" / ");
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

//****************************** Id detect ******************************
bool isObjectTarget(){
  int id_detected = 0;
  while(id_detected == 0){
    if(ReturnObjectCNT()<2){
      Serial.print("Object CNT == 1 / ");
      id_detected = IdReturn();
    }
    else{
      Serial.print("Object CNT >= 2 / ");
      id_detected = IdReturn_Closer();
    }
  }
  Serial.println("detected id : "+(String)(id_detected));
  if(id_detected == target_object)  return true;
  else return false;
}



int IdReturn(){
  if (!huskylens.request()) {
    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    return 0;
  } else if (!huskylens.isLearned()) {
    Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    return 0;
  } else if (!huskylens.available()) {
    Serial.println(F("No block or arrow appears on the screen!"));
    return 0;
  }
  else{
    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      if (result.command == COMMAND_RETURN_BLOCK) {
        if (result.ID == 1 || result.ID == 2 || result.ID == 3) {
          Serial.println(String()+F("Block ID=")+result.ID);
          return result.ID;
        }
      }
    }
  }
  return 0; // 반환할 객체 ID가 없으면 0을 반환
}

int IdReturn_Closer(){
  if (!huskylens.request()) {
    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    return 0;
  }
  else if (!huskylens.isLearned()) {
    Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    return 0;
  }
  else if (!huskylens.available()) {
    Serial.println(F("No block or arrow appears on the screen!"));
    return 0;
  }
  else {
    int maxArea = 0;    // 최대 면적 초기화
    int idOfLargest = 0; // 가장 큰 객체의 ID를 저장할 변수 초기화

    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      int area = result.width * result.height; // 현재 객체의 면적 계산
      if (area > maxArea) { // 현재 객체의 면적이 이전에 계산된 최대 면적보다 큰 경우
        maxArea = area;     // 최대 면적을 현재 면적으로 업데이트
        idOfLargest = result.ID; // 최대 면적을 가진 객체의 ID 저장
      }
    }
    return idOfLargest; // 가장 큰 면적을 가진 객체의 ID 반환
  }
}

int ReturnObjectCNT() {
  if (!huskylens.request()) {
    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    return 0;
  }
  else if (!huskylens.isLearned()) {
    Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    return 0;
  }
  else if (!huskylens.available()) {
    Serial.println(F("No block or arrow appears on the screen!"));
    return 0;
  }
  else {
    int objectCount = 0; // 객체 수를 세는 변수 초기화
    while (huskylens.available()) {
      huskylens.read(); // 객체 정보를 읽어오기만 하고 저장하지는 않음
      objectCount++;    // 읽어온 객체마다 카운트 증가
    }
    return objectCount; // 화면에 인식된 객체의 수 반환
  }
}