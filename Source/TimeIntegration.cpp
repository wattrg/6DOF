#include "TimeIntegration.H"
#include "DOF6.H"
#include "Vector3.H"

void advance (State& S, Projectile & B, double dt, int solver, bool do_aero, int do_grav, bool do_DOF, int nFoils) {
    

    if (solver == 1){
        euler_update (S, B, dt, do_aero, do_grav, do_DOF, nFoils);
    }
    else if (solver == 2){
        improved_euler (S, B, dt, do_aero, do_grav, do_DOF, nFoils);
    }
    else if (solver == 3) {
        RK4(S, B, dt, do_aero, do_grav, do_DOF, nFoils);
    }
    
}

void euler_update (State & S, Projectile & B, double dt, bool do_aero, int do_grav, bool do_DOF, int nFoils) {
    // S_new = S_old + f' * dt
    trans_rot accel = calc_dSdt(S, B, do_aero, do_grav, do_DOF, nFoils);
    S.vel = S.vel + dt*accel.translation;
    S.omega = S.omega + dt*accel.rotation;
    S.euler_rate = calc_euler_rate (S.omega, S.euler);
    S.euler = S.euler + dt*S.euler_rate;
    S.inert_vel = body2inert(S, B, S.vel);
    S.inert_pos = S.inert_pos + dt*S.inert_vel;
}

void improved_euler (State & S, Projectile & B, double dt, bool do_aero, int do_grav, bool do_DOF, int nFoils){
    State k1, k2;

    trans_rot accel = calc_dSdt(S, B, do_aero, do_grav, do_DOF, nFoils);

    // calculate k1
    k1.vel = dt*accel.translation;
    k1.omega = dt*accel.rotation;
    k1.euler_rate = calc_euler_rate(k1.omega, k1.euler);
    k1.euler = dt*S.euler_rate;
    k1.inert_vel = body2inert(S, B, k1.vel);
    k1.inert_pos = dt*S.inert_vel;
    
    
    // calculate k2
    State sum = S + k1;
    accel = calc_dSdt(sum, B, do_aero, do_grav, do_DOF, nFoils);
    k2.vel = dt*accel.translation;
    k2.omega = dt*accel.rotation;
    k2.euler_rate = calc_euler_rate(sum.omega, sum.euler);
    k2.euler = dt*sum.euler_rate;
    k2.inert_vel = body2inert(sum, B, sum.vel);
    k2.inert_pos = dt*sum.inert_vel;

    // calculate new state
    S = S + 0.5 * (k1 + k2);
    S.omega[0] = 0.0;
    S.omega[1] = 0.0;
    S.euler_rate = calc_euler_rate(S.omega, S.euler);
    S.inert_vel = body2inert(S, B, S.vel);

}

void RK4 (State & S, Projectile & B, double dt, bool do_aero, int do_grav, bool do_DOF, int nFoils){
    State k1, k2, k3, k4;

    trans_rot accel = calc_dSdt(S, B, do_aero, do_grav, do_DOF, nFoils);

    // calculate k1
    k1.vel = dt*accel.translation;
    k1.omega = dt*accel.rotation;
    k1.euler = dt*S.euler_rate;
    k1.euler_rate = calc_euler_rate(k1.omega, k1.euler);
    k1.inert_vel = body2inert(S, B, k1.vel);
    k1.inert_pos = dt*S.inert_vel;
    
    // calculate k2
    State sum = S + 0.5*k1;
    accel = calc_dSdt(sum, B, do_aero, do_grav, do_DOF, nFoils);
    k2.vel = dt*accel.translation;
    k2.omega = dt*accel.rotation;
    k2.euler_rate = calc_euler_rate(sum.omega, sum.euler);
    k2.euler = dt*sum.euler_rate;
    k2.inert_vel = body2inert(sum, B, sum.vel);
    k2.inert_pos = dt*sum.inert_vel;

    // calculate k3
    sum = S + 0.5*k2;
    accel = calc_dSdt(sum, B, do_aero, do_grav, do_DOF, nFoils);
    k3.vel = dt*accel.translation;
    k3.omega = dt*accel.rotation;
    k3.euler_rate = calc_euler_rate(sum.omega, sum.euler);
    k3.euler = dt*sum.euler_rate;
    k3.inert_vel = body2inert(sum, B, sum.vel);
    k3.inert_pos = dt*sum.inert_vel;

    // calculate k4
    sum = S + k3;
    accel = calc_dSdt(sum, B, do_aero, do_grav, do_DOF, nFoils);
    k4.vel = dt*accel.translation;
    k4.omega = dt*accel.rotation;
    k4.euler_rate = calc_euler_rate(sum.omega, sum.euler);
    k4.euler = dt*sum.euler_rate;
    k4.inert_vel = body2inert(sum, B, sum.vel);
    k4.inert_pos = dt*sum.inert_vel;

    // calculate updated state
    S = S + (1.0/6.0)*k1 + (1.0/3.0)*k2 + (1.0/3.0)*k3 + (1.0/6.0)*k4;
    S.omega[0] = 0.0;
    S.omega[1] = 0.0;
    S.euler_rate = calc_euler_rate(S.omega, S.euler);
    S.inert_vel = body2inert(S, B, S.vel);

}