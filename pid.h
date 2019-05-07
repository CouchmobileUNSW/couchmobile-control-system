// Include all the data structures and function declarations here

struct pid{
    double  _dt;
    double  _max;
    double  _min;
    double  _Kp;
    double  _Kd;
    double  _Ki;
    double  _pre_error;
    double  _integral;
};

double calculate(struct pid, double setpount, double pv);
