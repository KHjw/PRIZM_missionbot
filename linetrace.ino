//******************************ANALOG Linetrace******************************
void linetrace_analogPrint(int time) {
  int irData = analogRead(A1);
  if (irData >
      irDataMAX) {  // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
    irData = irDataMAX;
    Serial.print(F("irData calib -> "));
  }
  Serial.print((String)(irData) + ". ");
  if (testCNT > 10) {
    Serial.println(F(""));
    testCNT = 0;
  }
  testCNT++;
  delay(time);
}

void linetrace_analog() {
  int irData = analogRead(A1);
  if (irData >
      irDataMAX) {  // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
    irData = irDataMAX;
  }
  float sig = (irData - threshold) * gain;
  prizm.setMotorPowers(default_speed - sig, default_speed + sig);
  delay(20);
}

void linetrace_analogSetting(float gainData, int default_speedData,
                             int irDataMAXData) {
  gain = gainData;
  default_speed = default_speedData;
  irDataMAX = irDataMAXData;
  threshold = (irDataMAX + 19) / 2 + 1;
  Serial.print(F("LineTrace Setting:"));  // 세팅값 입력
  Serial.println("irDataMAX:" + (String)(irDataMAX) +
                 "  threshold:" + (String)(threshold) + "  default_speed:" +
                 (String)(default_speed) + "  gain:" + (String)(gain));
}

void linetrace_analogSetting(float gainData, int default_speedData,
                             int irDataMAXData, int thresholdData) {
  gain = gainData;
  default_speed = default_speedData;
  irDataMAX = irDataMAXData;
  threshold = thresholdData;
  Serial.print(F("LineTrace Setting:"));  // 세팅값 입력
  Serial.println("irDataMAX:" + (String)(irDataMAX) +
                 "  threshold:" + (String)(threshold) + "  default_speed:" +
                 (String)(default_speed) + "  gain:" + (String)(gain));
}

// count
void intersectionDETECT() {
  if (prizm.readLineSensor(2) == 1) {  // 검정에 닿았을 때
    intersectionCNT++;
    Serial.println("[[[intersectionDETECT]]] intersectionCNT : " +
                   (String)(intersectionCNT));  // digitalDETECT 출력
    GoForward(60, 15);
  }
  delay(20);
}