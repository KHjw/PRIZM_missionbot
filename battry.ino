// robot State Check
void battVoltagePrint(){
  int battVoltage = prizm.readBatteryVoltage();
  Serial.println("battVoltage : "+(String)(battVoltage/100)+"."+(String)(battVoltage%100)+"V");   // 현 배터리 전압 체크
}

void battVoltagePrint(int time){
  int battVoltage = prizm.readBatteryVoltage();
  Serial.println("battVoltage : "+(String)(battVoltage/100)+"."+(String)(battVoltage%100)+"V");   // 현 배터리 전압 체크
  delay(time);
}

void setBattVoltage2(float setVoltage){
  int time = 5000;
  battVoltagePrint();
  float battVoltage = prizm.readBatteryVoltage()/100.0;
  if(battVoltage > setVoltage){
    Serial.print("> battVoltage TOO HIGH");
    prizm.setMotorPowers(120,120);
  }
  else if(battVoltage < setVoltage-0.2){
    delay(1000);
    if(battVoltage >= setVoltage-0.2)
      time = 500;
    Serial.print("> battVoltage TOO LOW :: CHARGE RECOMMENDED");
    prizm.setMotorPowers(125,125);
  }
  else{
    Serial.print("> battVoltage JUST RIGHT");
    prizm.setMotorPowers(125,125);
    time = 500;
  }
  Serial.println("  Optimal setting : "+(String)(setVoltage));
  delay(time);
}