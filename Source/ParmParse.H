#include <lua.hpp>
#include <LuaBridge.h>
#include "Vector3.H"
#include <vector>

#ifndef ParmParse_H
#define ParmParse_H

class ParmParse {

    public:
        double dt;
        int solver;                           
        double start_time;                       
        double stop_time;                     
        
        int file_rate;                         
        int print_rate;
        
        double mass;                          

        double Ixx, Iyy, Izz, Ixy, Ixz, Iyz;                                

        double sweep;
        double cone;
        double pitch;
        double x_ac;

        Vector3 vel_init;          
        Vector3 pos_init;            
        Vector3 omega_init;            
        Vector3 euler_init; 

        bool do_aero;
        int do_grav;
        bool do_DOF;

        int nAirFoils;
        double arm_length;
        double cord;


        ParmParse (char * file);
};

#endif