#ifndef FIRSTSTATEMACHINE_H
#define FIRSTSTATEMACHINE_H

#include "LinearFunction.h"

enum STATE{NONE,INIT_DRIVE_LEFT, INIT_DRIVE_UP, IDLE, START_CLEANINGUNIT, DRIVE_TO_UPPER_ENDPOSITION, MOTOR_BREAK, DRIVE_TO_LOWER_ENDPOSITION, DRIVE_TO_THE_LEFT, DRIVE_TO_THE_RIGHT, STOP_EVERYTHING, EMERGENCY_HOLD};

class FirstStatemachine
{
public:
    bool output[8];
    /** Pinout
     * output[0] = EMERGENCY
     * output[1] = LED_START
     * output[2] = LED_STOP
     * output[3] = MOTOR_UP
     * output[4] = MOTOR_DOWN
     * output[5] = MOTOR_LEFT
     * output[6] = MOTOR_RIGHT
     * output[7] = CLEANINGUNIT
     */
    int cleaningunit_speed;
    bool blinking;
    int CurrentState;
private:
    STATE theState;
    LinearFunction lf;

    unsigned long stopButtonPressAtTime;
    unsigned long startButtonPressAtTime;
    unsigned long timeTravelRight;
    bool isStop;
    unsigned long timeStopDebounce;
    unsigned long stepCount;//y abschnitte zählen
public:
    FirstStatemachine(/* args */);
    void evaluationStates(bool startButton, bool sensorUp, bool sensorDown, bool sensorRight, bool sensorLeft, bool stopButton, bool emergencyHold, unsigned long time);
    void evaluationOutput();
};
#endif	// FIRSTSTATEMACHINE_H

