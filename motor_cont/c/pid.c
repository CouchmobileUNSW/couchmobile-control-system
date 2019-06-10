#include <stdio.h>
#include <stdlib.h>
//#include <pid.h>

struct pid{
    double dt;
    double max;
    double min;
    double Kp;
    double Kd;
    double Ki;
    double error;
    double integral;
};

double calculate(struct pid* controller, double measured, double predicted){
    double error = measured - predicted;

    double Pout = controller->Kp * error;
    
    controller->integral += error * controller->dt;
    double Iout = controller->Ki * controller->integral;

    double derivative = (error - controller->error) / controller->dt;
    double Dout = controller->Kd * derivative;

    double output = Pout + Iout + Dout;
    printf("output: %f\n", output);

    if(output > controller->max)
        output = controller->max;
    if(output < controller->min)
        output = controller->min;

    controller->error = error;

    return output;
}

int main(int argc, char *argv[]){
    // Initialise the controller struct
    struct pid* con = malloc(sizeof(struct pid));
    con->dt = 0.1;
    con->max = 100;
    con->min = -100;
    con->Kp = 0.1;
    con->Kd = 0.01;
    con->Ki = 0.5;
    con->error = 0;
    con->integral = 0;

    // Initialise the pins used for the encoder

    double mes = 20;
    double des = 40;

    // Loop forever
    
    // Get the inputs from the encoder

    // Calculate the next output

    // Output to the PWM

    for(int i=0; i < 500; i++){
        double inc = calculate(con, des, mes);
        printf("%d. Desired: %.0f, Measured: %7.3f, Increment: %7.3f\n",i, des, mes, inc); 
        mes += inc;
    }



    return 0;
}
