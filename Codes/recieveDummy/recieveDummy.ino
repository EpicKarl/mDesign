#include <stdlib.h>                   //für atoi() notwendig

byte bufferData[11] = {'0'};
char incomingData[10] = {'0'};
byte dataToSend[6] = {'0'};
byte old_dataToSend[6] = {'0'};
char tmp_state[2] = {'0'};

byte incomingSignal;
char state;


void setup() {
  Serial.begin(9600);
}

void recieveData(){
  //Serial.setTimeout(100);
  if(Serial.available()){
    incomingSignal = Serial.readBytes(bufferData, 11);
    tmp_state[0] = bufferData[0];
    tmp_state[1] = bufferData[1];
//    Serial.println(tmp_state[0]);
//    Serial.println(tmp_state[1]);
//    Serial.println(atoi(tmp_state)/10);
    state = atoi(tmp_state)/10;            //verwendet bufferData[0],[1] um aus 6 & 5 -> 0x65 -> 'A' zu machen (Durch 10 um eine nichterklärebare Null loszuwerden!)
    incomingData[0] = state;            //Zuweisungen in char Array für Server
    incomingData[1] = bufferData[2];
    incomingData[2] = bufferData[3];
    incomingData[3] = bufferData[4];
    incomingData[4] = bufferData[5];
    incomingData[5] = bufferData[6];
    incomingData[6] = bufferData[7];
    incomingData[7] = bufferData[8];
    incomingData[8] = bufferData[9];
    incomingData[9] = bufferData[10];
    for (auto &current : incomingData) {  //Lediglich Konsolenausgabe, ob Übertragung geklappt hat
      Serial.print(current);              //Funktioniert nicht wenn sendDataToSerial() verwendet wird
    }Serial.print("\n");
  }
}

void sendDataToSerial(){
  if(dataToSend[0] != old_dataToSend[0] || //sendet nur wenn sich irgendwas ändert
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
  delay(100);
  dataToSend[0] = '0';
  //sendDataToSerial();
  //delay(2000);
  }
