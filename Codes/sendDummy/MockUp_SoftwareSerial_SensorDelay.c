#include "Arduino.h"
#include "SoftwareSerial.h"

SoftwareSerial mySerial(2, 3); // TX, RX

byte dataToSend[10] = {};
byte old_dataToSend[10] = {};
byte dataRecieve[6] = {};
byte bufferData[6] = {};
byte incomingSignal;

int count;

void sendDataTomySerial(){
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
			dataToSend[0]= 'H';
			dataToSend[1]= 0;
			dataToSend[2]= 1;
			dataToSend[3]= 0;
			dataToSend[4]= 0;
			dataToSend[5]= 1;
			dataToSend[6]= 0;
			dataToSend[7]= 0;
			dataToSend[8]= 0;
			dataToSend[9]= 1;
			break;
		case 4:
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
		case 5:
			dataToSend[0]= 'J';
			dataToSend[1]= 0;
			dataToSend[2]= 0;
			dataToSend[3]= 0;
			dataToSend[4]= 1;
			dataToSend[5]= 0;
			dataToSend[6]= 1;     
			dataToSend[7]= 0;
			dataToSend[8]= 0;
			dataToSend[9]= 0;
			break;
		case 6:
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
		case 7:
			dataToSend[0]= 'F';
			dataToSend[1]= 1;
			dataToSend[2]= 0;
			dataToSend[3]= 0;
			dataToSend[4]= 0;
			dataToSend[5]= 1;
			dataToSend[6]= 0;     
			dataToSend[7]= 0;
			dataToSend[8]= 1;
			dataToSend[9]= 0;
			break;
		case 8:
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
			break;
		case 9:
			dataToSend[0]= 'I';
			dataToSend[1]= 0;
			dataToSend[2]= 0;
			dataToSend[3]= 1;
			dataToSend[4]= 0;
			dataToSend[5]= 0;
			dataToSend[6]= 0;     
			dataToSend[7]= 1;
			dataToSend[8]= 0;
			dataToSend[9]= 0;
			count = 0;
			break;
			default:
			break;
		}
	}else if(dataRecieve[0] == '1'){
		if(dataRecieve[3] == '1'){
			dataToSend[0]= 'E';
			dataToSend[1]= 0;
			dataToSend[2]= 0;
			dataToSend[3]= 0;
			dataToSend[4]= 1;
			dataToSend[5]= 0;
			dataToSend[6]= 1;     
			dataToSend[7]= 0;
			dataToSend[8]= 0;
			dataToSend[9]= 0;
		}else if(dataRecieve[4] == '1'){
			dataToSend[0]= 'D';
			dataToSend[1]= 0;
			dataToSend[2]= 0;
			dataToSend[3]= 1;
			dataToSend[4]= 0;
			dataToSend[5]= 0;
			dataToSend[6]= 0;     
			dataToSend[7]= 1;
			dataToSend[8]= 0;
			dataToSend[9]= 0;
		}else if(dataRecieve[1] == '1'){
			dataToSend[0]= 'B';
			dataToSend[1]= 1;
			dataToSend[2]= 0;
			dataToSend[3]= 0;
			dataToSend[4]= 0;
			dataToSend[5]= 0;
			dataToSend[6]= 0;     
			dataToSend[7]= 0;
			dataToSend[8]= 1;
			dataToSend[9]= 0;
		}else if(dataRecieve[2] == '1'){
			dataToSend[0]= 'C';
			dataToSend[1]= 0;
			dataToSend[2]= 1;
			dataToSend[3]= 0;
			dataToSend[4]= 0;
			dataToSend[5]= 0;
			dataToSend[6]= 0;     
			dataToSend[7]= 0;
			dataToSend[8]= 0;
			dataToSend[9]= 1;
		}else if(dataRecieve[5] == '1'){
			dataToSend[5]= 1;
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
    if (dataToSend[0] != old_dataToSend[0] || //sendet nur wenn sich irgendwas ändert
		dataToSend[1] != old_dataToSend[1] || 
		dataToSend[2] != old_dataToSend[2] ||
		dataToSend[3] != old_dataToSend[3] ||
		dataToSend[4] != old_dataToSend[4] ||
		dataToSend[5] != old_dataToSend[5] ||
		dataToSend[6] != old_dataToSend[6] ||
		dataToSend[7] != old_dataToSend[7] ||
		dataToSend[8] != old_dataToSend[8] ||
		dataToSend[9] != old_dataToSend[9]){ 
		for (int x = 0; x<10; x++){  
			mySerial.print(dataToSend[x]); 
		}
		for (int i = 0; i < 10; i++) {
			old_dataToSend[i] = dataToSend[i];
	    }
		if(dataRecieve[0] == '0'){
			delay(2000);
			count++;
		}	
	}
}

void recieveDataFrommySerial(){
	mySerial.setTimeout(100);
	if(mySerial.available()){
		incomingSignal = mySerial.readBytes(bufferData, 6);
		for(int i = 0; i < 6; i++){
			dataRecieve[i] = bufferData[i];
			Serial.print(dataRecieve[i] - '0');
		}
    Serial.println("");
	}
}

void setup() {
	Serial.begin(9600);
	mySerial.begin(9600);
}

void loop() {
	sendDataTomySerial();
	recieveDataFrommySerial();
}