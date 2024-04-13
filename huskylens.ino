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
