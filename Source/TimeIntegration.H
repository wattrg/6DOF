#include "State.H"
#include "Projectile.H"

#ifndef integration_h
#define integration_h

void advance (State& S, Projectile & B, double dt, int solver, bool do_aero, int do_grav, bool do_DOF, int nFoils);


void euler_update (State & S, Projectile & B, double dt, bool do_aero, int do_grav, bool do_DOF, int nFoils);
void improved_euler (State & S, Projectile& B, double dt, bool do_aero, int do_grav, bool do_DOF, int nFoils);
void RK4 (State & S, Projectile& B, double dt, bool do_aero, int do_grav, bool do_DOF, int nFoils);

#endif