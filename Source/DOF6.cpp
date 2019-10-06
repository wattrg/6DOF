#include "DOF6.H"
#include "Aerodynamics.H"
#include "State.H"
#include "Matrix3.H"
#include "Vector3.H"

trans_rot aero_forces (State & S, Projectile & B);

Matrix3 calc_inv_T (Vector3 & euler){
    double T_inv[3][3] = {
            cos(euler[1])*cos(euler[0]),
            -cos(euler[2])*sin(euler[0]) + sin(euler[2])*sin(euler[1])*cos(euler[0]),
            sin(euler[2])*sin(euler[0]) + cos(euler[2])*sin(euler[1])*cos(euler[0]),

            cos(euler[1])*sin(euler[0]),
            cos(euler[2])*cos(euler[0]) + sin(euler[2])*sin(euler[1])*sin(euler[0]), 
            -sin(euler[2])*cos(euler[0]) + cos(euler[2])*sin(euler[1])*sin(euler[0]),

            -sin(euler[1]),
            sin(euler[2])*cos(euler[1]),
            cos(euler[2])*cos(euler[1])
    };
    return Matrix3(T_inv);
}

Vector3 calc_euler_rate(Vector3 & omega, Vector3 & euler){
    Vector3 euler_rate;
    euler_rate[0] = omega[1]*sin(euler[2])/cos(euler[1]) 
                    + omega[2]*cos(euler[2])/cos(euler[1]);

    euler_rate[1] = omega[1]*cos(euler[2]) - omega[2] * sin(euler[2]);

    euler_rate[2] = omega[0] + omega[1]*sin(euler[2])*tan(euler[1]) 
                    + omega[2]*cos(euler[2])*tan(euler[1]);
    return euler_rate;
}

Vector3 calc_grav(State & S, Projectile & B){
    Vector3 grav (0., 0., -9.8);
    grav = inert2body(S, B, grav);
    return (B.mass * grav);
}

Vector3 body2inert (State & S, Projectile & B, Vector3 & vec){
    // flat earth vec = T0_inv * T_inv * body fixed vel
    Matrix3 invT = calc_inv_T(S.euler);
    //Matrix3 temp = B.invT0*invT;
    Matrix3 temp = invT;
    return temp*vec;
}

Vector3 inert2body (State & S, Projectile & B, Vector3 & vec){
    // body fixed vec = T * T0 * flat earth vec
    Matrix3 T = calc_inv_T(S.euler).T(); // since T is unitary, transposing it give its inverse
    //Matrix3 temp = T * B.T0;
    Matrix3 temp = T;
    return temp*vec;
}

trans_rot calc_dSdt (State & S, Projectile & B, bool do_aero, int do_grav, bool do_DOF, int nFoils){
    trans_rot aero_forces, accel;
    Vector3 F, M, fg;

    // calculate aerodynamic forces and moments
    if (do_aero == true){
        aero_forces = calc_aero_forces(S, B, nFoils);
    }
    else if (do_DOF == true){
        aero_forces = {Vector3 (0., 0., 0.), Vector3(1.,0.,0.)};
    }
    else {
        aero_forces = {Vector3 (0., 0., 0.), Vector3(0.,0.,0.)};
    }

    // calculate gravity
    if (do_grav == 1){
        fg = calc_grav(S, B);
    }
    else if (do_grav == 0){
        fg = Vector3 (0., 0., 0.);
    }
    else if (do_grav == 2){
        fg = Vector3 (0.0, 0.0, -9.81);
        fg = B.mass * fg;
    }

    // calculate translational accel
    F = aero_forces.translation + fg;
    Vector3 trans_inertia = cross(S.omega, S.vel);
    Vector3 temp1 = (1.0/B.mass)*F - trans_inertia;
    accel.translation = temp1;

    // calculate rotational accel
    M = aero_forces.rotation;
    Vector3 temp = B.I * S.omega;
    temp = cross(S.omega, temp);
    temp = M - temp;
    temp = B.invI*temp;
    accel.rotation = temp;


    return accel;
}

