#include "PID.h"
#include "stdio.h"

//calcul PID

float calculPID()
{
	integral += error * dt;
	derivative = (error - previousError) / dt;
	pidOutput = (Kp * error) + (Ki * integral) + (Kd * derivative);
}


//limit de PID

void LimitMax(int *input, int max)
    {
        if (input > max)
        {
            *input = max;
        }
        else if (input < -max)
        {
            *input = -max;
        }


    }

