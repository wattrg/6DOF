#include "Vector3.H"
#include "Matrix3.H"
#include "Projectile.H"



#ifndef DOF6_H
#define DOF6_H

class State;

// structure containing translational and rotational information
struct trans_rot {
    Vector3 translation;
    Vector3 rotation;
};

Vector3 body2inert (State & S, Projectile & B, Vector3 & vec);
Vector3 inert2body (State & S, Projectile & B, Vector3 & vec);

trans_rot calc_dSdt (State & S, Projectile & B, bool do_aero, int do_grav, bool do_DOF, int nFoils);

Matrix3 calc_inv_T (Vector3 & euler);
Vector3 calc_euler_rate(Vector3 & omega, Vector3 & euler);

#endif