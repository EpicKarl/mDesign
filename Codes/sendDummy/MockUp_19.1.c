
byte dataToSend[10] = {};
byte dataRecieve[6] = {'0'};
byte bufferData[6] = {};
byte incomingSignal;
int OldState;
int count;

void sendDataToSerial(){
  if(dataRecieve[0] == '0'){
    switch(count){      
      case 1:         
        dataToSend[0]= 'D'; 
        dataToSend[1]= 0;   
        dataToSend[2]= 0;   
        dataToSend[3]= 0;
        dataToSend[4]= 0;
        dataToSend[5]= 0;
        dataToSend[6]= 0;
        dataToSend[7]= 0;
        dataToSend[8]= 0;
        dataToSend[9]= 0;
        break;
      case 2:
        dataToSend[0]= 'H';
        dataToSend[1]= 0;
        dataToSend[2]= 1;
        dataToSend[3]= 0;
        dataToSend[4]= 0;
        dataToSend[5]= 1;
        dataToSend[6]= 0;
        dataToSend[7]= 0;
        dataToSend[8]= 0;
        dataToSend[9]= 0;
        break;
      case 3:
        dataToSend[0]= 'J';
        dataToSend[1]= 0;
        dataToSend[2]= 0;
        dataToSend[3]= 0;
        dataToSend[4]= 1;
        dataToSend[5]= 0;
        dataToSend[6]= 0;     
        dataToSend[7]= 0;
        dataToSend[8]= 0;
        dataToSend[9]= 0;
        break;
      case 4:
        dataToSend[0]= 'F';
        dataToSend[1]= 1;
        dataToSend[2]= 0;
        dataToSend[3]= 0;
        dataToSend[4]= 0;
        dataToSend[5]= 1;
        dataToSend[6]= 0;     
        dataToSend[7]= 0;
        dataToSend[8]= 0;
        dataToSend[9]= 0;
        break;
      case 5:
        dataToSend[0]= 'I';
        dataToSend[1]= 0;
        dataToSend[2]= 0;
        dataToSend[3]= 1;
        dataToSend[4]= 0;
        dataToSend[5]= 0;
        dataToSend[6]= 0;     
        dataToSend[7]= 0;
        dataToSend[8]= 0;
        dataToSend[9]= 0;
        count = 0;
        break;
        default:
        break;
    }
  }else if(dataRecieve[0] == '1'){
    if(dataRecieve[4] == '1'){
      dataToSend[0]= 'E';
      dataToSend[1]= 0;
      dataToSend[2]= 0;
      dataToSend[3]= 0;
      dataToSend[4]= 0;
      dataToSend[5]= dataRecieve[5];
      dataToSend[6]= 1;     
      dataToSend[7]= 0;
      dataToSend[8]= 0;
      dataToSend[9]= 0;
    }else if(dataRecieve[3] == '1'){
      dataToSend[0]= 'D';
      dataToSend[1]= 0;
      dataToSend[2]= 0;
      dataToSend[3]= 0;
      dataToSend[4]= 0;
      dataToSend[5]= dataRecieve[5];
      dataToSend[6]= 0;     
      dataToSend[7]= 1;
      dataToSend[8]= 0;
      dataToSend[9]= 0;
    }else if(dataRecieve[1] == '1'){
      dataToSend[0]= 'B';
      dataToSend[1]= 0;
      dataToSend[2]= 0;
      dataToSend[3]= 0;
      dataToSend[4]= 0;
      dataToSend[5]= dataRecieve[5];
      dataToSend[6]= 0;     
      dataToSend[7]= 0;
      dataToSend[8]= 1;
      dataToSend[9]= 0;
    }else if(dataRecieve[2] == '1'){
      dataToSend[0]= 'C';
      dataToSend[1]= 0;
      dataToSend[2]= 0;
      dataToSend[3]= 0;
      dataToSend[4]= 0;
      dataToSend[5]= dataRecieve[5];
      dataToSend[6]= 0;     
      dataToSend[7]= 0;
      dataToSend[8]= 0;
      dataToSend[9]= 1;
    }else{
	  dataToSend[0]= 'A';
      dataToSend[1]= 0;
      dataToSend[2]= 0;
      dataToSend[3]= 0;
      dataToSend[4]= 0;
      dataToSend[5]= 0;
      dataToSend[6]= 0;     
      dataToSend[7]= 0;
      dataToSend[8]= 0;
      dataToSend[9]= 0;
	}                 
  }
    if(dataToSend[0] != OldState){ //array wird nur gesendet, wenn sich dataToSend[0] --der state-- verändert
    for (int x = 0; x<10; x++){  
      Serial.print(dataToSend[x]); 
    }
    OldState = dataToSend[0];
  }
  if(dataRecieve[0] == '0'){
    delay(2000);
	count++;
  }
}

void recieveDataFromSerial(){
  Serial.setTimeout(100);
  if(Serial.available()){
    incomingSignal = Serial.readBytes(bufferData, 6);
    for(int i = 0; i < 6; i++){
      dataRecieve[i] = bufferData[i];
    }
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  sendDataToSerial();
  recieveDataFromSerial();
}
