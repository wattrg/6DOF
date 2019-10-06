#include "DOF6.H"

#ifndef Aerodynamics_H
#define Aerodynamics_H

trans_rot calc_aero_forces (State & S, Projectile B, int nFoils);
double trap_int (std::vector<double> integrands, double dx);
double CoeffL(double aoa);
double CoeffD (double aoa);
double CoeffM (double aoa);

#endif
