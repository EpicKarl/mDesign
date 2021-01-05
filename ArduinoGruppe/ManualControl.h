#ifndef MANUALCONTROL_H
#define MANUALCONTROL_H

#include <dos.h> 
#include<stdio.h>
#include<stdlib.h>

#include "LinearFunction.h"

enum STATE{NONE, DRIVE_UP, DRIVE_DOWN, DRIVE_LEFT, DRIVE_RIGHT, CLEANINGUNIT, MOTOR_BREAK, EMERGENCY_HOLD};


class ManualControl
{
public:
    bool output[8];
    /** Pinout
     * output[0] = MOTOR_UP
     * output[1] = MOTOR_DOWN
     * output[2] = MOTOR_LEFT
     * output[3] = MOTOR_RIGHT
     * output[4] = CLEANINGUNIT
     * output[5] = LIGHT_RED
     * output[6] = LIGHT_YELLOW
     * output[7] = LIGHT_GREEN
     */
	 
    bool input[6];
    /** Input
     * input[0] = BUTTON_UP
     * input[1] = BUTTON_DOWN
     * input[2] = BUTTON_LEFT
     * input[3] = BUTTON_RIGHT
     * input[4] = CLEANINGUNIT
     * input[4] = EMERGENCY_HOLD
     */
    int cleaningunit_speed;
    bool cleaningunit_state;
    unsigned long startButtonPressAtTime;
    STATE theState;
    int CurrentState;
	
private:
    //STATE theState;
    LinearFunction lf;
    char ButtonState;

public:
    ManualControl(/* args */);
    void evaluationInput(bool ButtonUp, bool ButtonDown, bool ButtonLeft, bool ButtonRight, bool CleaningUnit, bool EmergencyHold, bool ButtonReset, unsigned long time);
    void evaluationOutput();
    STATE getState();
};
#endif	// MANUALCONTROL_H

