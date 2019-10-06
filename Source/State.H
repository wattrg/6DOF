#include "Vector3.H"
#include "DOF6.H"
#include "Projectile.H"


#ifndef State_H
#define State_H



class State  {
    public:
        Vector3 euler_init;
        Vector3 vel, omega, euler_rate, inert_vel, inert_pos, euler;

        State(){
            Vector3 vel;
            Vector3 omega;
            Vector3 euler_rate;
            Vector3 inert_vel;
            Vector3 inert_pos;
            Vector3 euler;
            Vector3 euler_init;
        };

        State(Vector3 & v_init, Vector3 & omega_init, Vector3 & euler_init, Vector3 & pos_init, Projectile & B){
            vel = v_init;
            omega = omega_init;
            this -> euler_init = euler_init;
            euler = euler_init;
            inert_pos = pos_init;
            calc_euler_rate(omega, euler_init);
            inert_vel = B.T0 * v_init;
        };

        void calc_omega ();
        
};

State operator + (State a, State b);
State operator * (double alpha, State b);


#endif