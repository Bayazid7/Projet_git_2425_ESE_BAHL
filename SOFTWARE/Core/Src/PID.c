#include "PID.h"
#include "stdio.h"

//calcul PID

float calculPID(float error, float previousError, float dt, float Kp, float Ki, float Kd)
{
    static float integral = 0; // Utiliser static pour que la valeur reste entre les appels
    integral += error * dt;
    float derivative = (error - previousError) / dt;
    float pidOutput = (Kp * error) + (Ki * integral) + (Kd * derivative);
    return pidOutput;
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

