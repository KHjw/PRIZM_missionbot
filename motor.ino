void motorInit() {
  prizm.setMotorInvert(1, 1);
  prizm.setServoSpeed(1, 60);
  prizm.setServoSpeed(2, 60);
  prizm.setServoSpeed(3, 60);

  gripper_openPOS();
}

//****************************** gripper mode ******************************
void gripper_openPOS() {
  prizm.setServoPosition(1, servo1_openPOS);
  prizm.setServoPosition(2, servo2_openPOS);
}

void gripper_closePOS() {
  prizm.setServoPosition(1, servo1_closePOS);
  prizm.setServoPosition(2, servo2_closePOS);
}

void gripper_moveUP(int time) {
  prizm.setServoPosition(1, servo1_closePOS);
  prizm.setServoPosition(2, servo2_closePOS);
  prizm.setServoPosition(3, servo3_upPOS);
  delay(time);
}

//****************************** can grab ******************************
void canGrab() {
  if (!isCanGrab) {
    if (prizm.readSonicSensorCM(4) <= canDetectCm) {
      Serial.println(F("!!!Can Detected!!!"));
      StopFor(50);
      gripper_moveUP(100);
      isCanGrab = true;
      NODE_dataUpdate(currentNODE, 1);
      // if (NODE_dataReturn(NODE11) == 1 || NODE_dataReturn(NODE5) == 1)
      if (NODE_dataReturn(NODE5) == 1) intersectionCNT == 1;
      if (NODE_dataReturn(NODE7) == 2 && NODE_dataReturn(NODE11) == 1)
        intersectionCNT == 1;
      StopFor(1000);
    }
  }
}

void canApproach() {
  if (!isCanGrab) {
    Serial.print(F("can approach! / "));
    StopFor(100);
    int SQ_size = ReturnSquareSize();
    if (SQ_size > detectSize || prizm.readSonicSensorCM(4) <= canApproachCm) {
      Serial.println(SQ_size);
      Serial.println(F("!!!Can Approach!!!"));
      linetrace_analogSetting(0.7, 10, 40, 35);
      intersectionCNT = 0;
      while (!isCanGrab && intersectionCNT == 0) {
        canGrab();
        if (!(NODE_dataReturn(NODE5) == 0 && NODE_dataReturn(NODE9) != 1))
          intersectionDETECT();
        if (intersectionCNT > 0) break;
        linetrace_analog();
      }
      linetrace_analogSetting(3.0, 60, 40, 35);
      if (!(NODE_dataReturn(NODE3) == 0 && NODE_dataReturn(NODE5) == 0 &&
            NODE_dataReturn(NODE9) == 1))
        linetrace_analog(2);
    } else
      Serial.println(ReturnSquareSize());
  }
}

void canDrop() {
  StopFor(200);
  Serial.println(F("canDrop!!!"));
  gripper_openPOS();
}

//****************************** move mode ******************************
void TurnRight() {
  prizm.setMotorPowers(40, -40);
  delay(750);
  prizm.setMotorPowers(125, 125);  // 정지
  TurnCalib();
}

void TurnLeft() {
  prizm.setMotorPowers(-40, 40);
  delay(750);
  prizm.setMotorPowers(125, 125);  // 정지
  TurnCalib();
}

void TurnAround() {
  prizm.setMotorPowers(100, -100);
  delay(1000);
  prizm.setMotorPowers(125, 125);  // 정지
  TurnCalib();
}

void GoForward(int velocity, int time) {
  prizm.setMotorPowers(velocity, velocity);
  delay(time);
}

void StopFor(unsigned long time) {
  prizm.setMotorPowers(125, 125);  // 정지
  delay(time);
}

void TurnCalib() {
  StopFor(50);
  intersectionDETECT();
  if (intersectionCNT > 0) {
    Serial.println(F("TurnCalib"));
    prizm.setMotorPowers(40, -40);
    delay(50);
    StopFor(50);
  }
  intersectionCNT = 0;
}