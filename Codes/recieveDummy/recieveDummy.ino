byte incomingData[11] = {'0'};
byte incomingSignal;
byte dataToSend[6] = {0};
byte old_dataToSend[6] = {0};

void setup() {
  Serial.begin(9600);
}

void recieveData(){
  Serial.setTimeout(100);
  if(Serial.available()){
    incomingSignal = Serial.readBytes(incomingData, 11);
    if(incomingData[5]-'0' == 0){
      incomingData[5] = '0';
      incomingData[6] = '0';
    }
     for (auto &current : incomingData) {
      Serial.print(current-'0');
     }
     Serial.print("\n");
    /*Serial.print(incomingData[0]-'0');
    Serial.print(" ");
    Serial.print(incomingData[1]-'0');
    Serial.print(" ");
    Serial.print(incomingData[2]-'0');
    Serial.print(" ");
    Serial.print(incomingData[3]-'0');
    Serial.print(" ");
    Serial.print(incomingData[4]-'0');
    Serial.print(" ");
    Serial.print(incomingData[5]-'0');
    Serial.print(incomingData[6]-'0');
    Serial.print(" ");
    Serial.print(incomingData[7]-'0');
    Serial.print(" ");
    Serial.print(incomingData[8]);
    Serial.print(" ");
    Serial.print(incomingData[9]);
    Serial.print(" ");
    Serial.print(incomingData[10]);
    Serial.print(" ");       
    //Serial.print(incomingSignal);
    Serial.print("\n");*/
  }
}

void sendDataToSerial(){
  if(dataToSend[0] != old_dataToSend[0] || 
     dataToSend[1] != old_dataToSend[1] || 
     dataToSend[2] != old_dataToSend[2] ||
     dataToSend[3] != old_dataToSend[3] ||
     dataToSend[4] != old_dataToSend[4] ||
     dataToSend[5] != old_dataToSend[5]){
    for (auto &current : dataToSend) {
      Serial.print(current);
    }for (auto &current : dataToSend) {
      old_dataToSend[current] = dataToSend[current];
     }
  }
}

void loop() {
  recieveData();
  //sendDataToSerial();
  //delay(2000);
  }
