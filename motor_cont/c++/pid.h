// Include all the data structures and function declarations here

#ifndef PID_H
#define PID_H
// Class Definition
class pidControl {
    private:
        // PID constants
        double _dt;
        double _max;
        double _min;
        double _Kp;
        double _Kd;
        double _Ki;
        double _error;
        double _integral;

    public:
        pidControl(double dt, double max, double min, double Kp, double Kd, double Ki); // Constructor
        ~pidControl(); // Destructor

        // Class Functions
        // Calculate an appropriate output based on the desired and measured values
        double calculate(double desired, double measured);
};
#endif