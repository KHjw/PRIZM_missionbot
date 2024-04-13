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
      Serial.println("Can Detected!!!");
      gripper_moveUP(2000);
      isCanGrab = true;
    }
  }
}

//****************************** move mode ******************************
void TurnRignt(){
  Serial.println("TurnRignt");
  prizm.setMotorPowers(40, -40);
  delay(750);
  prizm.setMotorPowers(125, 125);   // 정지
}

void TurnLeft(){
  Serial.println("TurnLeft");
  prizm.setMotorPowers(-40, 40);
  delay(750);
  prizm.setMotorPowers(125, 125);   // 정지
}

void TurnAround(){
  Serial.println("TurnAround");
  prizm.setMotorPowers(100, -100);
  delay(1050);
  prizm.setMotorPowers(125, 125);   // 정지
}

void GoForward(int velocity, int time){
  Serial.println("GoForward");
  prizm.setMotorPowers(velocity, velocity);
  delay(time);
}

void StopFor(long time){
  prizm.setMotorPowers(125, 125);   // 정지
  delay(time);
}

void Wait(){
  prizm.setMotorPowers(125, 125);   // 정지
  ptrCurrentMode = voidFunc;
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