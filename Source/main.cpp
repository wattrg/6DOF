#include <iostream>
#include <ctime>
#include <fstream>
#include <math.h>

#include <lua.hpp>
#include <LuaBridge.h>

#include "Vector3.H"
#include "Matrix3.H"
#include "Projectile.H"
#include "DOF6.H"
#include "State.H"
#include "WriteFile.H"
#include "TimeIntegration.H"
#include "ParmParse.H"


int main (int argc, char *argv[]) {

    // Initialse
    std::cout << "Initialsing \n\n";
    //--------------------------------- Inputs ---------------------------------------

    

    ParmParse pp(argv[1]);
    

    double dt = pp.dt;                            // seconds
    int solver = pp.solver;                              // 1: euler, 2: improved euler, 3: RK4
    double start_time = pp.start_time;                       // seconds
    double stop_time = pp.stop_time;                      // seconds
    
    int file_rate = pp.file_rate;                          // time steps between outputting to file
    int print_rate = pp.print_rate;
    
    double mass = pp.mass;                           // kg

    double I_array[3][3] = {   
         pp.Ixx, -pp.Ixy, -pp.Ixz, 
        -pp.Ixy,  pp.Iyy, -pp.Iyz,
        -pp.Ixz, -pp.Iyz,  pp.Izz 
    };                                       // kg m^2

    double sweep = pp.sweep;
    double cone = pp.cone;
    double pitch = pp.pitch;
    double x_ac = pp.x_ac;

    Vector3 vel_init = pp.vel_init;              // m/s    (body frame)
    Vector3 pos_init = pp.pos_init;             // m      (inertial frame)
    Vector3 omega_init = pp.omega_init;               // rad/s  (body frame)
    Vector3 euler_init = pp.euler_init;              // rad
    //---------------------------------------------------------------------------------


    Matrix3 I (I_array);

    std::cout << "dt         = " << dt << std::endl; 
    std::cout << "do_aero    = " << pp.do_aero << std::endl;
    std::cout << "I          = "; I.print();
    std::cout << "mass       =  " << mass << std::endl;
    std::cout << "sweep      = " << sweep << std::endl;
    std::cout << "cone       = " << cone << std::endl;
    std::cout << "pitch      = " << pitch << std::endl;
    std::cout << "x_ac       = " << x_ac << std::endl;
    std::cout << "vel_init   = "; vel_init.print();
    std::cout << "pos_init   = "; pos_init.print();
    std::cout << "omega_init = "; omega_init.print();
    std::cout << "euler_init = "; euler_init.print();
    

    std::ofstream outfile;
    outfile.open("trajectory.csv");
    
    int Nt = 0;
    double time = start_time;

    Matrix3 invT0 = calc_inv_T(euler_init);

    Projectile B (I, invT0, mass, sweep,cone, pitch, x_ac, pp.arm_length, pp.cord);
    

    State S (vel_init, omega_init, euler_init, pos_init, B);


    // output initial state
    outfile << "t,u,v,w,e1,e2,e3,p,q,r,vx,vy,vz,x,y,z\n";
    write_file(outfile, S, time);

    std::cout << "Initialised \n \n";

    std::cout << "Beginning Run \n" << std::endl;
    clock_t t_start;
    t_start = clock();


    // Begin Simulating

    while (time < stop_time && S.inert_pos[2] > 0){
        advance (S, B, dt, solver, pp.do_aero, pp.do_grav, pp.do_DOF, pp.nAirFoils);
        time += dt;
        Nt += 1;


        if (file_rate != 0 && Nt % file_rate == 0){
            write_file(outfile, S, time);
        }  

        if (print_rate != 0 && Nt % print_rate == 0){
            std::cout << "t = " << time << std::endl;
            std::cout << "body fixed velocity: "; S.vel.print();
            std::cout << "inertial velocity: "; S.inert_vel.print();
            std::cout << "position: "; S.inert_pos.print();
            std::cout << std::endl;
        }     
    }

    // output final state
    write_file(outfile, S, time);

    outfile.close();

    std::cout << "Run Complete, time taken: " << (double)(clock() - t_start)/CLOCKS_PER_SEC << " seconds \n \n";

    std::cout << "Information about trajectory: \n";
    std::cout << "flight time = " << time << std::endl;
    std::cout << "landing position: "; S.inert_pos.print();

    


    return 0;
}