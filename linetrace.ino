//******************************DIGITAL Linetrace******************************
void linetrace_digitalPrint(int time){
  if(prizm.readLineSensor(2) == 1){   // 검정에 닿았을 때
    Serial.println("1");              // . 출력
  }
  else{                               // 흰색에 닿았을 때
    Serial.print(".");                // 1 출력
  }
  delay(time);
}

void linetrace_digital(){
  if(prizm.readLineSensor(2) == 0){   // 흰색에 닿았을 때
    Serial.print(".");                // . 출력
    prizm.setMotorPowers(10,125);
  }
  else{                               // 검정색에 닿았을 때
    Serial.println("1");              // 1 출력
    prizm.setMotorPowers(125,10);
  }
  delay(100);
}

//******************************ANALOG Linetrace******************************
void linetrace_analogPrint(int time){
  int irData = analogRead(A1); 
  if(irData > irDataMAX){       // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
    irData = irDataMAX;
    Serial.print("irData calib -> "); 
  }
  Serial.print((String)(irData)+". ");
  if(testCNT > 10){
    Serial.print("\n");
    testCNT = 0;
  }
  testCNT ++;
  delay(time);
}

void linetrace_analog(){
  int irData = analogRead(A1); 
  if(irData > irDataMAX){       // irData 값이 비정상적으로 높을 때, irDataMAX로 보정
    irData = irDataMAX;
    // Serial.print("irData calib -> "); 
  }
  float sig = (irData-threshold)*gain;
  // Serial.print((String)(irData)+ " ("+(String)(sig)+"/"+(String)(default_speed-sig)+"). ");
  prizm.setMotorPowers(default_speed-sig, default_speed+sig);
  delay(20);
}

void linetrace_analogSetting(float gainData, int default_speedData, int irDataMAXData){
  gain = gainData;
  default_speed = default_speedData;
  irDataMAX = irDataMAXData;
  threshold = (irDataMAX + 19)/2+1;
  Serial.print("LineTrace Setting:");         // 세팅값 입력
  Serial.println("irDataMAX:"+(String)(irDataMAX)+"  threshold:"+(String)(threshold)+"  default_speed:"+(String)(default_speed)+"  gain:"+(String)(gain));
}

void linetrace_analogSetting(float gainData, int default_speedData, int irDataMAXData, int thresholdData){
  gain = gainData;
  default_speed = default_speedData;
  irDataMAX = irDataMAXData;
  threshold = thresholdData;
  Serial.print("LineTrace Setting:");         // 세팅값 입력
  Serial.println("irDataMAX:"+(String)(irDataMAX)+"  threshold:"+(String)(threshold)+"  default_speed:"+(String)(default_speed)+"  gain:"+(String)(gain));
}

// count
void intersectionDETECT(){
  if(prizm.readLineSensor(2) == 1){   // 검정에 닿았을 때
    intersectionCNT++;
    Serial.print("\n\n[[[intersectionDETECT]]] intersectionCNT : " + (String)(intersectionCNT)+"\n\n");    // digitalDETECT 출력
    GoForward(60, 15);
  }
  delay(20);
}