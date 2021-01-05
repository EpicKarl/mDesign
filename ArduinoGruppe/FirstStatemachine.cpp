#include "FirstStatemachine.h"

#define TRAVELTIMERIGHT 10 //defines in seconds
#define MAXSTEPS 99

FirstStatemachine::FirstStatemachine(/* args */)
{
    output[0] = 0;//EMERGENCY
    output[1] = 0;//LED_START
    output[2] = 0;//LED_STOP
    output[3] = 0;//MOTOR_UP
    output[4] = 0;//MOTOR_DOWN
    output[5] = 0;//MOTOR_LEFT
    output[6] = 0;//MOTOR_RIGHT
    output[7] = 0;//CLEANINGUNIT print when high
    stopButtonPressAtTime = 0;
    startButtonPressAtTime = 0;
    timeTravelRight = 0;
    stepCount = 0;
    theState = NONE;
    isStop = false;
    cleaningunit_speed = 0;
    blinking = 0;
}

void FirstStatemachine::evaluationStates(bool startButton, bool sensorUp, bool sensorDown, bool sensorRight, bool sensorLeft, bool stopButton, bool emergencyHold, unsigned long time)
{
    if(emergencyHold)
    {
        theState = EMERGENCY_HOLD;
        cleaningunit_speed = lf.countingDown(time);
    }    
    else if(stopButton && theState != EMERGENCY_HOLD && !isStop)
    {
        theState = STOP_EVERYTHING;
    }
    else if(isStop && !stopButton && time > timeStopDebounce+100)//[TODO] Button bounce?
    {
        isStop = false;
        timeStopDebounce = time;
    }
    if(stepCount > MAXSTEPS)
    {
        theState = STOP_EVERYTHING;
        cleaningunit_speed = lf.countingDown(time);
    }


    switch(theState)
    {
        case NONE:
            if(startButton)
            {
                theState = INIT_DRIVE_LEFT;
            }
        break;
        case INIT_DRIVE_LEFT:
            if(sensorLeft)
            {
                if(sensorUp)
                {
                    theState = IDLE;
                }
                else
                {
                    theState = INIT_DRIVE_UP;
                }
            }
        break;
        case INIT_DRIVE_UP:
            if(sensorUp)
            {
                theState = IDLE;
                lf.setCounterZero();
            }
        break;   
        case IDLE:
            if(startButton)
            {
                theState = START_CLEANINGUNIT;
            }
        break;
        case START_CLEANINGUNIT:
            cleaningunit_speed = lf.countingUp(time);
            if(LINEARFUNCTION_MAXSTEP == cleaningunit_speed)
            {
                theState = DRIVE_TO_LOWER_ENDPOSITION;
            }
        break;
        case DRIVE_TO_LOWER_ENDPOSITION:
            if(sensorDown)
            {
                theState = MOTOR_BREAK;
            }
        break;
        case MOTOR_BREAK:
            cleaningunit_speed = lf.countingDown(time);
            if(LINEARFUNCTION_MINSTEP == cleaningunit_speed)
            {
                theState = DRIVE_TO_UPPER_ENDPOSITION;
            }
        break;
        case DRIVE_TO_UPPER_ENDPOSITION:
            if(sensorUp && !sensorRight)
            {
                theState = DRIVE_TO_THE_RIGHT;
                timeTravelRight = time;
                stepCount++;

            }
            else if(sensorUp && sensorRight)
            {
                theState = DRIVE_TO_THE_LEFT;
            }
        break;
        case DRIVE_TO_THE_RIGHT:
            if(sensorRight || (time > (timeTravelRight + TRAVELTIMERIGHT*1000)))//Timer einstellen für Fahrtlänge
            {
                theState = START_CLEANINGUNIT;
            }
        break;
        case DRIVE_TO_THE_LEFT:
            if(sensorLeft)
            {
                lf.setCounterZero();
                theState = IDLE;
            }
        break;
        case STOP_EVERYTHING:
            if(startButton)
            {
                if(sensorUp)
                {
                    theState = IDLE;
                }
                else if(sensorLeft)
                {
                    theState = INIT_DRIVE_UP;
                }
                stopButtonPressAtTime = 0;
            }
            else if(stopButton)   //Timer für 5 Sekunden
            {
                if(0 == stopButtonPressAtTime)
                {
                    stopButtonPressAtTime = time;
                }
                else if(time > stopButtonPressAtTime+5000)
                {
                    theState = INIT_DRIVE_LEFT;
                    stopButtonPressAtTime = 0;
                    isStop = true;
                }
            }
            else if(!stopButton)
            {
                stopButtonPressAtTime = 0;
            }
            cleaningunit_speed = lf.countingDown(time);
        break;
        case EMERGENCY_HOLD:
            if(startButton)
            {
                if(0 == startButtonPressAtTime)
                {
                    startButtonPressAtTime = time;
                }
                else if(time > startButtonPressAtTime+3000)
                {
                    if(sensorUp)
                    {
                        theState = IDLE;
                    }
                    else if(sensorLeft)
                    {
                        theState = INIT_DRIVE_UP;
                    }
                    startButtonPressAtTime = 0;
                }
            }
            else if(!startButton)
            {
                startButtonPressAtTime = 0;
            }
        break;
    }
}

void FirstStatemachine::evaluationOutput()
{
    switch(theState)
    {   
        case INIT_DRIVE_LEFT:
            output[0] = 0;//EMERGENCY
            output[1] = 1;//LED_START  //blinking
            output[2] = 0;//LED_STOP
            output[3] = 0;//MOTOR_UP
            output[4] = 0;//MOTOR_DOWN
            output[5] = 1;//MOTOR_LEFT
            output[6] = 0;//MOTOR_RIGHT
            output[7] = 0;//CLEANINGUNIT
            blinking = 1;
            CurrentState = theState;
        break;
        case INIT_DRIVE_UP:
            output[0] = 0;//EMERGENCY
            output[1] = 1;//LED_START  //blinking
            output[2] = 0;//LED_STOP
            output[3] = 1;//MOTOR_UP
            output[4] = 0;//MOTOR_DOWN
            output[5] = 0;//MOTOR_LEFT
            output[6] = 0;//MOTOR_RIGHT
            output[7] = 0;//CLEANINGUNIT
            blinking = 1;
            CurrentState = theState;
        break;   
        case IDLE:
            output[0] = 0;//EMERGENCY
            output[1] = 1;//LED_START
            output[2] = 0;//LED_STOP
            output[3] = 0;//MOTOR_UP
            output[4] = 0;//MOTOR_DOWN
            output[5] = 0;//MOTOR_LEFT
            output[6] = 0;//MOTOR_RIGHT
            output[7] = 0;//CLEANINGUNIT
            blinking = 0;
            CurrentState = theState;
        break;
            case START_CLEANINGUNIT:
            output[0] = 0;//EMERGENCY
            output[1] = 0;//LED_START
            output[2] = 0;//LED_STOP
            output[3] = 0;//MOTOR_UP
            output[4] = 0;//MOTOR_DOWN
            output[5] = 0;//MOTOR_LEFT
            output[6] = 0;//MOTOR_RIGHT
            output[7] = 1;//CLEANINGUNIT
            blinking = 0;
            CurrentState = theState; 
        break;
        case DRIVE_TO_LOWER_ENDPOSITION:
            output[0] = 0;//EMERGENCY
            output[1] = 0;//LED_START
            output[2] = 0;//LED_STOP
            output[3] = 0;//MOTOR_UP
            output[4] = 1;//MOTOR_DOWN
            output[5] = 0;//MOTOR_LEFT
            output[6] = 0;//MOTOR_RIGHT
            output[7] = 1;//CLEANINGUNIT
            blinking = 0;
            CurrentState = theState;  
        break;
        case MOTOR_BREAK:
            output[0] = 0;//EMERGENCY
            output[1] = 0;//LED_START
            output[2] = 0;//LED_STOP
            output[3] = 0;//MOTOR_UP
            output[4] = 0;//MOTOR_DOWN
            output[5] = 0;//MOTOR_LEFT
            output[6] = 0;//MOTOR_RIGHT
            output[7] = 1;//CLEANINGUNIT
            blinking = 0;
            CurrentState = theState;
        break;
        case DRIVE_TO_UPPER_ENDPOSITION:
            output[0] = 0;//EMERGENCY
            output[1] = 0;//LED_START
            output[2] = 0;//LED_STOP
            output[3] = 1;//MOTOR_UP
            output[4] = 0;//MOTOR_DOWN
            output[5] = 0;//MOTOR_LEFT
            output[6] = 0;//MOTOR_RIGHT
            output[7] = 0;//CLEANINGUNIT
            blinking = 0;
            CurrentState = theState;   
        break;
        case DRIVE_TO_THE_RIGHT:
            output[0] = 0;//EMERGENCY
            output[1] = 0;//LED_START
            output[2] = 0;//LED_STOP
            output[3] = 0;//MOTOR_UP
            output[4] = 0;//MOTOR_DOWN
            output[5] = 0;//MOTOR_LEFT
            output[6] = 1;//MOTOR_RIGHT
            output[7] = 0;//CLEANINGUNIT
            blinking = 0;
            CurrentState = theState; 
        break;
        case DRIVE_TO_THE_LEFT:
            output[0] = 0;//EMERGENCY
            output[1] = 0;//LED_START
            output[2] = 0;//LED_STOP
            output[3] = 0;//MOTOR_UP
            output[4] = 0;//MOTOR_DOWN
            output[5] = 1;//MOTOR_LEFT
            output[6] = 0;//MOTOR_RIGHT
            output[7] = 0;//CLEANINGUNIT
            blinking = 0;
            CurrentState = theState;  
        break;
        case STOP_EVERYTHING:
            output[0] = 1;//EMERGENCY
            output[1] = 0;//LED_START
            output[2] = 1;//LED_STOP
            output[3] = 0;//MOTOR_UP
            output[4] = 0;//MOTOR_DOWN
            output[5] = 0;//MOTOR_LEFT
            output[6] = 0;//MOTOR_RIGHT
            output[7] = 0;//CLEANINGUNIT
            blinking = 0;
            CurrentState = theState;  
        break;
        case EMERGENCY_HOLD:
            output[0] = 1;//EMERGENCY
            output[1] = 0;//LED_START
            output[2] = 1;//LED_STOP
            output[3] = 0;//MOTOR_UP
            output[4] = 0;//MOTOR_DOWN
            output[5] = 0;//MOTOR_LEFT
            output[6] = 0;//MOTOR_RIGHT
            output[7] = 0;//CLEANINGUNIT
            blinking = 0;
            CurrentState = theState;
        break;
    }
}