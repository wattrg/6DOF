#include "Vector3.H"
#include "Matrix3.H"
#include <vector>


#ifndef Projectile_H
#define Projectile_H

class Projectile {
    public:
        Matrix3 I, invI, T0, invT0;
        std::vector<Matrix3> T_blade, inv_T_blade;
        double x_ac, sweep, cone, pitch, mass, arm_length, cord;

        Projectile(Matrix3 & I, Matrix3 & invT0, double & mass, double & sweep,
                     double & cone, double & pitch, double & x_ac, double & arm_length, double & cord){
            this -> I = I;
            invI = I.inv();
            this -> invT0 = invT0;
            T0 = invT0.T();
            this -> x_ac = x_ac;
            this -> mass = mass;
            this -> sweep = sweep;
            this -> cone = cone;
            this -> pitch = pitch;
            T_blade.push_back(Tj(sweep, cone, pitch));
            inv_T_blade.push_back(T_blade[0].inv());
            T_blade.push_back(Tj(-sweep, cone, pitch));
            inv_T_blade.push_back(T_blade[1].inv());
            this-> arm_length = arm_length;
            this-> cord = cord;
        };

        // transformation between body fixed coordinates and blade fixed coordinates
        Matrix3 Tj (double sweep, double cone, double pitch);
        
                
};

#endif