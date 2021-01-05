#include "ManualControl.h"

ManualControl::ManualControl(){
    output[0] = 0;//MOTOR_UP
    output[1] = 0;//MOTOR_DOWN
    output[2] = 0;//MOTOR_LEFT
    output[3] = 0;//MOTOR_RIGHT
    output[4] = 0;//CLEANINGUNIT
    output[5] = 0;//LIGHT_RED
    output[6] = 0;//LIGHT_YELLOW
    output[7] = 0;//LIGHT_GREEN
	
//    input[0] = 0;//BUTTON_UP
//    input[1] = 0;//BUTTON_DOWN
//    input[2] = 0;//BUTTON_LEFT
//    input[3] = 0;//BUTTON_RIGHT
//    input[4] = 0; //CLEANING_UNIT
//    input[5] = 0; //EmergencyHold
//    input[6] = 0; //ButtonReset
    theState = NONE;
    cleaningunit_speed = 0;
    cleaningunit_state = 0;
    startButtonPressAtTime = 0;
}

void ManualControl::evaluationInput(bool ButtonUp, bool ButtonDown, bool ButtonLeft, bool ButtonRight, bool CleaningUnit,  bool EmergencyHold, bool StartButton, unsigned long time){
    ButtonState = (char) ButtonUp + (char) ButtonDown + (char) ButtonLeft + (char) ButtonRight + (char) CleaningUnit; 
    
//    input[0] = ButtonUp; 
//    input[1] = ButtonDown;
//    input[2] = ButtonLeft;
//    input[3] = ButtonRight;
//    input[4] = CleaningUnit; 
//    input[5] = EmergencyHold; 
//    input[6] = ButtonReset; 
    
    if(EmergencyHold)
    {
        theState = EMERGENCY_HOLD;
    }
    
    switch(theState)
    {
        case NONE:
            //lf.setCounterZero();
            startButtonPressAtTime = 0;
            if(EmergencyHold)
            {
                theState = EMERGENCY_HOLD;
            }
            else if((ButtonState > 1 && cleaningunit_state == 0) || (ButtonState > 1+1 && cleaningunit_state == 1))
            {
                theState = NONE;
            }
            else if(EmergencyHold){
                theState = EMERGENCY_HOLD;
            }
            else if(ButtonUp)
            {
                theState = DRIVE_UP;
            }
            else if(ButtonDown)
            {
                theState = DRIVE_DOWN;
            }
            else if(ButtonRight)
            {
                theState = DRIVE_RIGHT;
            }
            else if(ButtonLeft)
            {
                theState = DRIVE_LEFT;
            }
            else if(CleaningUnit == 0 && cleaningunit_state)
            {
                cleaningunit_state = 0;
                theState = MOTOR_BREAK;
            }
            else if(CleaningUnit)
            {
                cleaningunit_state = 1;
                theState = CLEANINGUNIT;
            }
        break;
        case DRIVE_UP:
            if(EmergencyHold)
            {
                theState = EMERGENCY_HOLD;
            }
            else if((ButtonState > 1 && cleaningunit_state == 0) || (ButtonState > 1+1 && cleaningunit_state == 1))
            {
                theState = NONE;
            }
            else if(ButtonLeft)
            {
                theState = DRIVE_LEFT;
            }
            else if(ButtonDown)
            {
                theState = DRIVE_DOWN;
            }
            else if(ButtonRight)
            {
                theState = DRIVE_RIGHT;
            }
            else if(CleaningUnit == 0 && cleaningunit_state)
            {
                cleaningunit_state = 0;
                theState = MOTOR_BREAK;
            }
            else if(CleaningUnit)
            {
                cleaningunit_state = 1;
                theState = CLEANINGUNIT;
            }
        break;
        case DRIVE_DOWN:
            if(EmergencyHold)
            {
                theState = EMERGENCY_HOLD;
            }
            else if((ButtonState > 1 && cleaningunit_state == 0) || (ButtonState > 1+1 && cleaningunit_state == 1))
            {
                theState = NONE;
            }
            else if(ButtonUp)
            {
                theState = DRIVE_UP;
            }
            else if(ButtonLeft)
            {
                theState = DRIVE_LEFT;
            }
            else if(ButtonRight)
            {
                theState = DRIVE_RIGHT;
            }
            else if(CleaningUnit == 0 && cleaningunit_state)
            {
                cleaningunit_state = 0;
                theState = MOTOR_BREAK;
            }
            else if(CleaningUnit)
            {
                cleaningunit_state = 1;
                theState = CLEANINGUNIT;
            }
        break;
        case DRIVE_LEFT:
            if(EmergencyHold)
            {
                theState = EMERGENCY_HOLD;
            }
            else if((ButtonState > 1 && cleaningunit_state == 0) || (ButtonState > 1+1 && cleaningunit_state == 1))
            {
                theState = NONE;
            }
            else if(ButtonUp)
            {
                theState = DRIVE_UP;
            }
            else if(ButtonDown)
            {
                theState = DRIVE_DOWN;
            }
            else if(ButtonRight)
            {
                theState = DRIVE_RIGHT;
            }
            else if(CleaningUnit == 0 && cleaningunit_state)
            {
                cleaningunit_state = 0;
                theState = MOTOR_BREAK;
            }
            else if(CleaningUnit)
            {
                cleaningunit_state = 1;
                theState = CLEANINGUNIT;
            }
        break;
        case DRIVE_RIGHT:
            if(EmergencyHold)
            {
                theState = EMERGENCY_HOLD;
            }
            else if((ButtonState > 1 && cleaningunit_state == 0) || (ButtonState > 1+1 && cleaningunit_state == 1))
            {
                theState = NONE;
            }
            else if(ButtonUp)
            {
                theState = DRIVE_UP;
            }
            else if(ButtonDown)
            {
                theState = DRIVE_DOWN;
            }
            else if(ButtonLeft)
            {
                theState = DRIVE_LEFT;
            }
            else if(CleaningUnit == 0 && cleaningunit_state)
            {
                cleaningunit_state = 0;
                theState = MOTOR_BREAK;
            }
            else if(CleaningUnit)
            {
                cleaningunit_state = 1;
                theState = CLEANINGUNIT;
            }
        break;
        
        case CLEANINGUNIT:
            cleaningunit_speed = lf.countingUp(time);
            
            if(180 == cleaningunit_speed)
            {
                if(EmergencyHold)
                {
                    theState = EMERGENCY_HOLD;
                }
                else if((ButtonState > 1 && cleaningunit_state == 0) || (ButtonState > 1+1 && cleaningunit_state == 1))
                {
                    theState = NONE;
                }
                else if(ButtonUp)
                {
                    theState = DRIVE_UP;
                }
                else if(ButtonLeft)
                {
                    theState = DRIVE_LEFT;
                }
                else if(ButtonRight)
                {
                    theState = DRIVE_RIGHT;
                }
                else if(CleaningUnit == 0 && cleaningunit_state)
                {
                    cleaningunit_state = 0;
                    theState = MOTOR_BREAK;
                }
            }
            
        break;
        
        case MOTOR_BREAK:
            while(LINEARFUNCTION_MINSTEP < cleaningunit_speed)
            {
                cleaningunit_speed = lf.countingDown(time);
            }
            
            if(LINEARFUNCTION_MINSTEP == cleaningunit_speed)
            {
                if(EmergencyHold)
                {
                    theState = EMERGENCY_HOLD;
                }
                else if((ButtonState > 1 && cleaningunit_state == 0) || (ButtonState > 1+1 && cleaningunit_state == 1))
                {
                    theState = NONE;
                }
                else if(ButtonUp)
                {
                    theState = DRIVE_UP;
                }
                else if(ButtonLeft)
                {
                    theState = DRIVE_LEFT;
                }
                else if(ButtonRight)
                {
                    theState = DRIVE_RIGHT;
                }
                else if(CleaningUnit)
                {
                    cleaningunit_state = 1;
                    theState = CLEANINGUNIT;
                }
            }
        break;
        case EMERGENCY_HOLD:
            cleaningunit_speed = 0;
            cleaningunit_state = 0;
            
            if(StartButton)
            {
                if(0 == startButtonPressAtTime)
                {
                    startButtonPressAtTime = time;
                }
                else if(time > startButtonPressAtTime+3000)
                {
                    theState = NONE;
                }
            }
            else if(!StartButton)
            {
                startButtonPressAtTime = 0;
            }
        break;
    }
}

void ManualControl::evaluationOutput(){
    switch(theState)
    {   
        case NONE:
            output[0] = 0;//MOTOR_UP
            output[1] = 0;//MOTOR_DOWN
            output[2] = 0;//MOTOR_LEFT
            output[3] = 0;//MOTOR_RIGHT
            output[4] = cleaningunit_state;
            output[5] = 0;//LIGHT_RED
            output[6] = 1;//LIGHT_YELLOW
            output[7] = 0;//LIGHT_GREEN
            CurrentState = theState;
        break;
        case DRIVE_UP:
            output[0] = 1;//MOTOR_UP
            output[1] = 0;//MOTOR_DOWN
            output[2] = 0;//MOTOR_LEFT
            output[3] = 0;//MOTOR_RIGHT
            output[4] = cleaningunit_state;
            output[5] = 0;//LIGHT_RED
            output[6] = 0;//LIGHT_YELLOW
            output[7] = 1;//LIGHT_GREEN
            CurrentState = theState;
        break;
        case DRIVE_DOWN:
            output[0] = 0;//MOTOR_UP
            output[1] = 1;//MOTOR_DOWN
            output[2] = 0;//MOTOR_LEFT
            output[3] = 0;//MOTOR_RIGHT
            output[4] = cleaningunit_state;
            output[5] = 0;//LIGHT_RED
            output[6] = 0;//LIGHT_YELLOW
            output[7] = 1;//LIGHT_GREEN
            CurrentState = theState;
        break;
        case DRIVE_LEFT:
            output[0] = 0;//MOTOR_UP
            output[1] = 0;//MOTOR_DOWN
            output[2] = 1;//MOTOR_LEFT
            output[3] = 0;//MOTOR_RIGHT
            output[4] = cleaningunit_state;
            output[5] = 0;//LIGHT_RED
            output[6] = 0;//LIGHT_YELLOW
            output[7] = 1;//LIGHT_GREEN
            CurrentState = theState;
        break;
        case DRIVE_RIGHT:
            output[0] = 0;//MOTOR_UP
            output[1] = 0;//MOTOR_DOWN
            output[2] = 0;//MOTOR_LEFT
            output[3] = 1;//MOTOR_RIGHT
            output[4] = cleaningunit_state;
            output[5] = 0;//LIGHT_RED
            output[6] = 0;//LIGHT_YELLOW
            output[7] = 1;//LIGHT_GREEN
            CurrentState = theState;
        break;
            
        case CLEANINGUNIT:
            output[0] = 0;//MOTOR_UP
            output[1] = 0;//MOTOR_DOWN
            output[2] = 0;//MOTOR_LEFT
            output[3] = 0;//MOTOR_RIGHT
            output[4] = cleaningunit_state;
            output[5] = 0;//LIGHT_RED
            output[6] = 0;//LIGHT_YELLOW
            output[7] = 1;//LIGHT_GREEN
            CurrentState = theState;
        break;
        
        case MOTOR_BREAK:
            output[0] = 0;//MOTOR_UP
            output[1] = 0;//MOTOR_DOWN
            output[2] = 0;//MOTOR_LEFT
            output[3] = 0;//MOTOR_RIGHT
            output[4] = cleaningunit_state;
            output[5] = 0;//LED_STOP
            output[5] = 0;//LIGHT_RED
            output[6] = 0;//LIGHT_YELLOW
            output[7] = 1;//LIGHT_GREEN
            CurrentState = theState;
        break;
        
        case EMERGENCY_HOLD:
            output[0] = 0;//MOTOR_UP
            output[1] = 0;//MOTOR_DOWN
            output[2] = 0;//MOTOR_LEFT
            output[3] = 0;//MOTOR_RIGHT
            output[4] = cleaningunit_state;
            output[5] = 1;//LIGHT_RED
            output[6] = 0;//LIGHT_YELLOW
            output[7] = 0;//LIGHT_GREEN
            CurrentState = theState;
        break;
    }
}
