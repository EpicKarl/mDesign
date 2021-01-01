
byte dataToSend[10] = {0};
int OldState;
int count;

void sendDataToSerial(){		//Dummy, der alle 2 Sekunden das Sensorabbild wechsel
      switch(count){			//0000000000
        case 1:					//11000901100
          dataToSend[0]= 0;		//20100451010
          dataToSend[1]= 0;		//30010791001
          dataToSend[2]= 0;		//Nachrichtlänge variiert also, muss bei empfang angepasst werden
          dataToSend[3]= 0;
          dataToSend[4]= 0;
          dataToSend[5]= 0;
          dataToSend[6]= 0;
		  dataToSend[7]= 0;
		  dataToSend[8]= 0;
		  dataToSend[9]= 0;
          break;
        case 2:
          dataToSend[0]= 1;
          dataToSend[1]= 1;
          dataToSend[2]= 0;
          dataToSend[3]= 0;
          dataToSend[4]= 0;
          dataToSend[5]= 90;
          dataToSend[6]= 1;
		  dataToSend[7]= 1;
		  dataToSend[8]= 0;
		  dataToSend[9]= 0;
          break;
        case 3:
          dataToSend[0]= 2;
          dataToSend[1]= 0;
          dataToSend[2]= 1;
          dataToSend[3]= 0;
          dataToSend[4]= 0;
          dataToSend[5]= 45;
          dataToSend[6]= 1;		  
		  dataToSend[7]= 0;
		  dataToSend[8]= 1;
		  dataToSend[9]= 0;
          break;
        case 4:
          dataToSend[0]= 3;
          dataToSend[1]= 0;
          dataToSend[2]= 0;
          dataToSend[3]= 1;
          dataToSend[4]= 0;
          dataToSend[5]= 70;
          dataToSend[6]= 1;		  
		  dataToSend[7]= 0;
		  dataToSend[8]= 0;
		  dataToSend[9]= 1;
          count = 0;
          break;
          default:
          break;
      }
      if(dataToSend[0] != OldState){ //array wird nur gesendet, wenn sich dataToSend[0] --der state-- verändert
      for (int x = 0; x<7; x++){	 //verwendet Arduinogruppe so beinhaltet aber, dass FSM korrekt funktioniert
        Serial.print(dataToSend[x]); 
      }
      OldState = dataToSend[0];
    }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  sendDataToSerial();
  count++;
  delay(2000);
}
