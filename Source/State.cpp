#include "State.H"

State operator + (State a, State b){
    State sum;
    sum.vel = a.vel + b.vel;
    sum.omega = a.omega + b.omega;
    sum.euler = a.euler + b.euler;
    sum.euler_rate = a.euler_rate + b.euler_rate;
    sum.inert_vel = a.inert_vel + b.inert_vel;
    sum.inert_pos = a.inert_pos + b.inert_pos;
    return sum;
}

State operator * (double alpha, State b){
    State prod;
    prod.vel = alpha*b.vel;
    prod.omega = alpha * b.omega;
    prod.euler = alpha * b.euler;
    prod.euler_rate = alpha * b.euler_rate;
    prod.inert_vel = alpha * b.inert_vel;
    prod.inert_pos = alpha * b.inert_pos;
    return prod;
}