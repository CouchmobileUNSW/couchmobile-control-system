#ifndef PID_H
#define PID_H

// PID controller class
class pid{
  public:
    pid(double dt, double max, double min, double Kp, double Kd, double Ki); // Constructor
    double calculate(double measured, double predicted); // Calculate output for the PID

  // Private variables
  private:
    double dt;        // Time interval
    double Max;       // Maximum possible value
    double Min;       // Minimum possible value
    double Kp;        // P constant
    double Kd;        // I constant
    double Ki;        // D constant
    double error;     // Current error calculated
    double integral;  // Current integral calculated
};

// Initialise the PID struct
// We use list initialisation here because it's cool and neat
pid::pid(double dt, double Max, double Min, double Kp, double Kd, double Ki) :
  dt(dt),
  Max(Max),
  Min(Min),
  Kp(Kp),
  Kd(Kd),
  Ki(Ki),
  error(0),
  integral(0) {
}

// Calculate the next output for the PID controller
double pid::calculate(double measured, double predicted){
  double curr_error = measured - predicted; // Get the current error

  // Find the current integral and derivative
  integral += curr_error * dt;
  double derivative = (error - curr_error) / dt;
  
  // Calculate the next output
  double Pout = Kp * curr_error;
  double Iout = Ki * integral;
  double Dout = Kd * derivative;
  double output = Pout + Iout + Dout;

  // Make sure the output is within bounds
  if(output > Max) output = Max;
  if(output < Min) output = Min;

  error = curr_error; // Update the error
  
  return output; // return the control value
}

#endif
