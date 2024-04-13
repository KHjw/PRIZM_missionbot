void motorInit(){
  prizm.setMotorInvert(1,1);

  prizm.setServoSpeed(1,60);
  prizm.setServoSpeed(2,60);
  prizm.setServoSpeed(3,10);
  
  gripper_openPOS();
}

//****************************** gripper mode ******************************
void gripper_openPOS(){
  prizm.setServoPosition(1,servo1_openPOS);
  prizm.setServoPosition(2,servo2_openPOS);
}

void gripper_closePOS(){
  prizm.setServoPosition(1,servo1_closePOS);
  prizm.setServoPosition(2,servo2_closePOS);
}

void gripper_moveUP(int time){
  prizm.setServoPosition(1,servo1_closePOS);
  prizm.setServoPosition(2,servo2_closePOS);
  prizm.setServoPosition(3,servo3_upPOS);
  delay(time);
}

void canGrab(){
  if(!isCanGrab){
    if(prizm.readSonicSensorCM(4) <= canDetectCm){
      prizm.setMotorPowers(125,125);  // 정지
      Serial.println(F("Can Detected!!!"));
      gripper_moveUP(2000);
      isCanGrab = true;
    }
  }
}

//****************************** move mode ******************************
void TurnRight(){
  prizm.setMotorPowers(40, -40);
  delay(750);
  prizm.setMotorPowers(125, 125);   // 정지
  TurnCalib();
}

void TurnLeft(){
  prizm.setMotorPowers(-40, 40);
  delay(750);
  prizm.setMotorPowers(125, 125);   // 정지
  TurnCalib();
}

void TurnAround(){
  prizm.setMotorPowers(100, -100);
  delay(1050);
  prizm.setMotorPowers(125, 125);   // 정지
  TurnCalib();
}

void GoForward(int velocity, int time){
  prizm.setMotorPowers(velocity, velocity);
  delay(time);
}

void StopFor(unsigned long time){
  prizm.setMotorPowers(125, 125);   // 정지
  delay(time);
}

void TurnCalib(){
  StopFor(50);
  intersectionDETECT();
  if(intersectionCNT > 0){
    Serial.println(F("TurnCalib"));
    prizm.setMotorPowers(40, -40);
    delay(50);
    StopFor(50);
  }
  intersectionCNT = 0;
}

//****************************** return home ******************************
void return_from9(){
  if(return_to == GREEN){
  }
  else if(return_to == RED){
  }
  else if(return_to == BLUE){
  }
  // can drop
}

void return_from5(){
  if(return_to == GREEN){
  }
  else if(return_to == RED){
  }
  else if(return_to == BLUE){
  }
  // can drop
}

void return_from1(){
  if(return_to == GREEN){
  }
  else if(return_to == RED){
  }
  else if(return_to == BLUE){
  }
  // can drop
}