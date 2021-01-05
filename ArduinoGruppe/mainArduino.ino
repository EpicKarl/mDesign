/** This class only call's other classes.
 * No logic will be here implemented.
 */
#define VERSION 4

#include <Servo.h> 

#include "src/FirstStatemachine.h"
#include "src/LinearFunction.h"
#include <SoftwareSerial.h>
#include "src/ManualControl.h"


//Wenn "#define DEBUG" auskommentiert ist(//) dann ist der Produktionsbetrieb aktiviert
//#define DEBUG

#ifdef DEBUG  //#ifdef tests if sequences are defined
#include "src/ComponentTest.h"
ComponentTest ct;
String incoming = "";
int altState = 0;
LinearFunction lf;
#endif

#ifndef DEBUG
FirstStatemachine fsm;
ManualControl manual;
#endif

#define EMRGENCY_HOLD A0
#define START_BUTTON A1
#define STOP_BUTTON A2
#define SENSOR_UP A3
#define SENSOR_DOWN A4
#define SENSOR_LEFT A5
#define SENSOR_RIGHT A6
#define ANALOG_THRESHOLD 500 // define .... V?

#define MOTOR_UP 28						// R6 - linkslauf M-yAchse
#define MOTOR_DOWN 29					// R7 - rechtslauf M-yAchse
#define MOTOR_LEFT 30					// R8 - linkslauf M-xAchse
#define MOTOR_RIGHT 31					// R9 - rechtslauf M-xAchse
#define MOTOR_CLEANINGUNIT 2			// D0 
#define LED_START 8						// D6
#define LED_STOP 9						// D7
//#define LIGHT_RED //welche PIN
//#define LIGHT_YELLOW //welche PIN
//#define LIGHT_GREEN //welche PIN

#define X_SENSOR_DELAY 2000
bool leftDelay;
bool rightDelay;
unsigned long timeLeftDelay;
unsigned long timeRightDelay;

unsigned long timeLeftDelayHOLD;
unsigned long timeRightDelayHOLD;

bool input[7];
Servo Servo1;
unsigned long timeBlink;

int incomingSignal; //this is for serial read
int OldState; //to look there is any change to the current state

// This Method will be called ones when the Arduino starts befor the loop
void setup()
{
  // Pin Mode
	pinMode(LED_START, OUTPUT);
	pinMode(LED_STOP, OUTPUT);
	pinMode(MOTOR_UP, OUTPUT);
	pinMode(MOTOR_DOWN, OUTPUT);
	pinMode(MOTOR_LEFT, OUTPUT);
	pinMode(MOTOR_RIGHT, OUTPUT);

  //UART Communication with Wifi Module
  Serial1.begin(115200); //why Serial1 ? because we use tx1 (pin 18) and rx1 (pin19) 


#ifdef DEBUG //#ifdef tests if sequences are defined
	Serial.begin(115200);
	Serial.println('\n\nDEBUG');
	delay(100);
	Serial.println('Now in Debug mode!');
#endif
	//Switch 6: R/C Mode/Microcontroller mode select
	//1 = 0
	//2 = 1
	//3 = 1
	//4 = 0
	//5 = 1
	//6 = 0
	Servo1.attach(MOTOR_CLEANINGUNIT); //Attach the Servo variable to a pin
	leftDelay = false;
	rightDelay = false;
	timeLeftDelay = 0;
	timeRightDelay = 0;
	timeLeftDelayHOLD = 0;
	timeRightDelayHOLD = 0;
}

// This Method will be called again when it reached the end
void loop()
{
	input[0] = 0; // = EMRGENCY_HOLD
	input[1] = 0; // = START_BUTTON
	input[2] = 0; // = STOP_BUTTON
	input[3] = 0; // = SENSOR_UP
	input[4] = 0; // = SENSOR_DOWN
	input[5] = 0; // = SENSOR_LEFT
	input[6] = 0; // = SENSOR_RIGHT

	//[TODO] BUG wenn alles if, der Controller hängt sich auf
	if(analogRead(EMRGENCY_HOLD) < ANALOG_THRESHOLD)
	{
		input[0] = 1;
	}
	if(analogRead(STOP_BUTTON) > ANALOG_THRESHOLD)
	{
		input[2] = 1;
	}
	if(analogRead(START_BUTTON) > ANALOG_THRESHOLD)
	{
		input[1] = 1;
	}
	if(analogRead(SENSOR_UP) > ANALOG_THRESHOLD)
	{
		input[3] = 1;
	}
	if(analogRead(SENSOR_DOWN) > ANALOG_THRESHOLD)
	{
		input[4] = 1;
	}
	if(analogRead(SENSOR_LEFT) < ANALOG_THRESHOLD)//???
	{
		// if(!leftDelay)
		// {
		// 	timeLeftDelay = millis()+X_SENSOR_DELAY;
		// }
		// if(millis() > timeLeftDelay)
		// {
			input[5] = 1;
		// 	timeLeftDelayHOLD = 1;
		// 	leftDelay = false;
		// }
		// leftDelay = true;
	}
	if(analogRead(SENSOR_RIGHT) < ANALOG_THRESHOLD)//???
	{
		// if(!rightDelay)
		// {
		// 	timeRightDelay = millis()+X_SENSOR_DELAY;
		// }
		// if(millis() > timeRightDelay)
		// {
			input[6] = 1;
		// 	timeRightDelayHOLD = 1;
		// 	rightDelay = false;
		// }
		// rightDelay = true;
	}

	/*if(timeLeftDelayHOLD > 0)
	{
		input[5] = 1;
		timeLeftDelayHOLD++;
		if(timeLeftDelayHOLD > 100)
		{
			timeLeftDelayHOLD = 0;
		}
	}

	if(timeRightDelayHOLD > 0)
	{
		input[6] = 1;
		timeRightDelayHOLD++;
		if(timeRightDelayHOLD > 100)
		{
			timeRightDelayHOLD = 0;
		}
	}*/

#ifndef DEBUG // it tests if a word has not been defined.

  char incomingData[8]={0};
  Serial1.setTimeout(100);
  incomingSignal = Serial1.readBytes(incomingData, 8); //read incoming signal as bytes
  
  //MANUAL ON 
  if(incomingSignal > 0 && incomingData[0]-'0' == 1){
    //why minus '0' ? The ASCII codes for the digits 0 through 9 is 48 through 57. 
    //When the character '0' is received it actually has a value of 48. 
    //The character '1' has the value 49, '2' has the value 50, and so on.
    //So to convert from the character '0' (which has a value of 48) to its numeric value, 
    //you need to subtract '0' which is the same as 48. and to get the numeric value of 1 
    //you can also substract character '1' to '0'(50-49 = 1)
    //this trick only work for number character1
    manual.evaluationInput(incomingData[1]-'0', incomingData[2]-'0', incomingData[3]-'0', incomingData[4]-'0', incomingData[5]-'0', incomingData[6]-'0', incomingData[7]-'0', millis());
    manual.evaluationOutput();
    digitalWrite(MOTOR_UP      , manual.output[0]);
    digitalWrite(MOTOR_DOWN     , manual.output[1]);
    digitalWrite(MOTOR_LEFT     , manual.output[2]);
    digitalWrite(MOTOR_RIGHT    , manual.output[3]);

    Servo1.write(LINEARFUNCTION_NULLPOINT-manual.cleaningunit_speed);

    //Send Serial Data
    char signalToSend[10] = {0};
    signalToSend[0] = manual.CurrentState;
    signalToSend[1] = manual.output[0]; //motor up
    signalToSend[2] = manual.output[1];//motor down
    signalToSend[3] = manual.output[2];//motor left
    signalToSend[4] = manual.output[3];//motor right
    signalToSend[5] = manual.output[4];//cleaningunit
    signalToSend[6] = input[6];//sensor right
    signalToSend[7] = input[5];//sensor left
    signalToSend[8] = input[3];//sensor up
    signalToSend[9] = input[4];//sensor down
  
    if(signalToSend[0] != OldState){//is there any state change ? when yes then send a new data
      for (int x = 0; x<10; x++){
        Serial1.print(signalToSend[x]); 
      }  
      OldState = signalToSend[0];
    }  
  }

  else{ //MANUAL OFF
    fsm.evaluationStates(input[1], input[3], input[4],input[6], input[5], input[2], input[0], millis());
    fsm.evaluationOutput();

    digitalWrite(LED_STOP     , fsm.output[2]);
    digitalWrite(MOTOR_UP     , fsm.output[3]);
    digitalWrite(MOTOR_DOWN     , fsm.output[4]);
    digitalWrite(MOTOR_LEFT     , fsm.output[5]);
    digitalWrite(MOTOR_RIGHT    , fsm.output[6]);
 

    //Send Serial Data
    char signalToSend[10] = {0};
    signalToSend[0] = fsm.CurrentState;
    signalToSend[1] = fsm.output[3]; //Motor Up
    signalToSend[2] = fsm.output[4];//Motor Down
    signalToSend[3] = fsm.output[5];//Motor Left
    signalToSend[4] = fsm.output[6];//Motor Right
    signalToSend[5] = fsm.output[7];//Cleaningunit
    signalToSend[6] = input[6];//Sensor Right
    signalToSend[7] = input[5];//Sensor Left
    signalToSend[8] = input[3];//Sensor Up
    signalToSend[9] = input[4];//Sensor Down

    if(signalToSend[0] != OldState){//is there any state change ? when yes then send a new data
      for (int x = 0; x<10; x++){
        Serial1.print(signalToSend[x]); 
      }  
      OldState = signalToSend[0];
    }
     
  
  
    if(fsm.blinking) 
    {
      if(millis() > timeBlink)
      {
        if(digitalRead(LED_START))
        {
          digitalWrite(LED_START, LOW); // pin off
        }
        else
        {
          digitalWrite(LED_START, HIGH); // pin on 
        }
        timeBlink = millis() +1000;
      }
    }
    else
    {
      digitalWrite(LED_START, fsm.output[1]);
    }

    Servo1.write(LINEARFUNCTION_NULLPOINT-fsm.cleaningunit_speed); // Motor Cleaningunit
  }
	
#endif

 
#ifdef DEBUG //#ifdef tests if sequences are defined
	if(ct.getState() != altState)
	{
		switch (ct.getState())
		{
		case 1:
			Serial.print("Version:");
			Serial.println(VERSION, DEC);
			Serial.println("Please Press START Button");
			break;
		case 2:
			Serial.println("START Button Pressed!");
			Serial.println("Please Press EMRGENCY Button");
			break;
		case 3:
			Serial.println("EMRGENCY Button Pressed!");
			Serial.println("Please Press STOP Button");
			break;
		case 4:
			Serial.println("STOP Button Pressed!");
			Serial.println("Please Hold Metal In Front Of The Upper Sensor");
			break;
		case 5:
			Serial.println("SensorUp Activated!");
			Serial.println("Please Hold Metal In Front Of The Lower Sensor");
			break;
		case 6:
			Serial.println("SensorDown Activated!");
			Serial.println("Please Hold Metal In Front Of The Left Sensor");
			break;
		case 7:
			Serial.println("SensorLeft Activated!");
			Serial.println("Please Hold Metal In Front Of The Right Sensor");
			break;			
		case 8:
			Serial.println("SensorRight Activated!");
			Serial.println("Please Press START Button To Drive Down(Bremsweg?)");
			break;
		case 9:
			Serial.println("Driving Down!");
			Serial.println("Please Wait Until SensorDown Is Reached");
			break;
		case 10:
			Serial.println("SensorDown Activated!");
			Serial.println("Please Press START Button To Drive Right");
			break;
		case 11:
			Serial.println("Driving Right!");
			Serial.println("Please Wait Until SensorRight Is Reached");
			break;
		case 12:
			Serial.println("SensorRight Activated!");
			Serial.println("Please Press START Button To Start Cleaningunit");
			break;
		case 13:
			Serial.println("Cleaningunit Running!");
			Serial.println("Please Press STOP Button");
			break;
		case 14:
			Serial.println("Cleaningunit Has Been Stopped!");
      Serial.println("Please Press START Button To Test The Lights!");
			break;
    case 15:
      Serial.println("The Lights Are ON!");
      Serial.println("Please Press STOP Button To Complete The Test!");
      break;
    case 16:
      Serial.println("Robot Has Been Successfully Tested!");
      break;
		}
		altState = ct.getState();
	}

  // Get the number of bytes (characters) available for reading from the serial port. This is data that’s 
  // already arrived and stored in the serial receive buffer (which holds 64 bytes).
	if (Serial.available() > 0)
	{
		incoming = Serial.readString(); 
    //reads characters from the serial buffer into a String. 
    //The function terminates if it times out (see setTimeout()).
    
		int incomingByte = incoming.toInt();
		Serial.print("I received: ");
		Serial.println(incomingByte, DEC);
		ct.doNow(incomingByte, input[1], input[3], input[4],input[6], input[5], input[2], input[0], millis());
	}

	ct.doNow(0, input[1], input[3], input[4],input[6], input[5], input[2], input[0], millis());
	
	if(!input[0]) // if NOT Taster nicht betätigt ist
	{
		digitalWrite(LED_START			, ct.output[1]);
		digitalWrite(LED_STOP			, ct.output[2]);
		digitalWrite(MOTOR_UP			, ct.output[3]);
		digitalWrite(MOTOR_DOWN			, ct.output[4]);
		digitalWrite(MOTOR_LEFT			, ct.output[5]);
		digitalWrite(MOTOR_RIGHT		, ct.output[6]);
    //digitalWrite(LIGHT_RED      , ct.output[8]);
    //digitalWrite(LIGHT_YELLOW     , ct.output[9]);
    //digitalWrite(LIGHT_GREEN     , ct.output[10]);
	}
	else // if NOT Taster betätigt ist
	{
		digitalWrite(LED_START			, 0);
		digitalWrite(LED_STOP			, 0);
		digitalWrite(MOTOR_UP			, 0);
		digitalWrite(MOTOR_DOWN			, 0);
		digitalWrite(MOTOR_LEFT			, 0);
		digitalWrite(MOTOR_RIGHT		, 0);
    //digitalWrite(LIGHT_RED      , 0);
    //digitalWrite(LIGHT_YELLOW     , 0);
    //digitalWrite(LIGHT_GREEN     , 0);
	}
	

	if(!ct.output[7] || input[0]) // if the State EMERGENCY HOLD nicht aktiv und der NOT Taster gedrückt ist
	{
		Servo1.write(LINEARFUNCTION_NULLPOINT-lf.countingDown(millis()));
	}
	else if(ct.output[7]) // if the State EMERGENCY HOLD aktiv
	{
		Servo1.write(LINEARFUNCTION_NULLPOINT-lf.countingUp(millis())); 
	}
#endif
}
