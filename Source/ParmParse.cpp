#include "ParmParse.H"
#include <iostream>

using namespace luabridge;

ParmParse::ParmParse(char * file){
    std::cout << file << std::endl;
    lua_State * L = luaL_newstate();

    luaL_openlibs(L);

    getGlobalNamespace(L)
        .beginClass<Vector3>("Vector3")
            .addConstructor<void(*) (double, double, double)>()
        .endClass();

    luaL_dofile(L, file);
    lua_pcall(L, 0, 0, 0);

    LuaRef lua_aero (L, new bool);
    lua_aero = lua_aero = getGlobal(L, "do_aero");
    if (lua_aero.isNil()) {
        std::cout << "do_aero not found!" << std::endl;
    }
    this->do_aero = lua_aero.cast<bool>();

    LuaRef lua_grav (L, new int);
    lua_grav = lua_grav = getGlobal(L, "do_grav");
    if (lua_grav.isNil()) {
        std::cout << "do_grav not found!" << std::endl;
    }
    this->do_grav = lua_grav.cast<int>();

    LuaRef lua_nFoils (L, new int);
    lua_nFoils = lua_nFoils = getGlobal(L, "nFoils");
    if (lua_nFoils.isNil()) {
        std::cout << "nFoils not found!" << std::endl;
    }
    this->nAirFoils = lua_nFoils.cast<int>();

    LuaRef lua_DOF6 (L, new bool);
    lua_DOF6 = getGlobal(L, "do_DOF6_check");
    if (lua_DOF6.isNil()) {
        std::cout << "do_DOF6_check not found!" << std::endl;
    }
    this->do_DOF = lua_DOF6.cast<bool>();

    LuaRef lua_arm_length (L, new double);
    lua_arm_length = getGlobal(L, "arm_length");
    if (lua_arm_length.isNil()) {
        std::cout << "arm_length not found!" << std::endl;
    }
    this->arm_length = lua_arm_length.cast<double>();

    LuaRef lua_cord (L, new double);
    lua_cord = getGlobal(L, "cord");
    if (lua_cord.isNil()) {
        std::cout << "cord not found!" << std::endl;
    }
    this->cord = lua_cord.cast<double>();

    LuaRef lua_dt (L, new double);
    lua_dt = lua_dt = getGlobal(L, "dt");
    if (lua_dt.isNil()) {
        std::cout << "dt not found!" << std::endl;
    }
    this->dt = lua_dt.cast<double>();

    LuaRef lua_solver (L, new int);
    lua_solver = getGlobal(L, "solver");
    if (lua_solver.isNil()) {
        std::cout << "solver not found!" << std::endl;
    }
    this->solver = lua_solver.cast<int>();

    LuaRef lua_start (L, new double);
    lua_start = getGlobal(L, "start_time");
    if (lua_start.isNil()) {
        std::cout << "start_time not found!" << std::endl;
    }
    this->start_time = lua_start.cast<double>();

    LuaRef lua_stop (L, new double);
    lua_stop = getGlobal(L, "stop_time");
    if (lua_stop.isNil()) {
        std::cout << "stop_time not found!" << std::endl;
    }
    this->stop_time = lua_stop.cast<double>();

    LuaRef lua_fr (L, new int);
    lua_fr = getGlobal(L, "file_rate");
    if (lua_fr.isNil()) {
        std::cout << "file_rate not found!" << std::endl;
    }
    this->file_rate = lua_fr.cast<int>();

    LuaRef lua_pr (L, new int);
    lua_pr = getGlobal(L, "print_rate");
    if (lua_pr.isNil()) {
        std::cout << "print_rate not found!" << std::endl;
    }
    this->print_rate = lua_pr.cast<int>();

    LuaRef lua_m (L, new double);
    lua_m = getGlobal(L, "mass");
    if (lua_m.isNil()) {
        std::cout << "mass not found!" << std::endl;
    }
    this->mass = lua_m.cast<double>();

    LuaRef lua_Ixx (L, new double);
    lua_Ixx = getGlobal(L, "Ixx");
    if (lua_Ixx.isNil()) {
        std::cout << "Ixx not found!" << std::endl;
    }
    this->Ixx = lua_Ixx.cast<double>();

    LuaRef lua_Iyy (L, new double);
    lua_Iyy = getGlobal(L, "Iyy");
    if (lua_Iyy.isNil()) {
        std::cout << "Iyy not found!" << std::endl;
    }
    this->Iyy = lua_Iyy.cast<double>();

    LuaRef lua_Izz (L, new double);
    lua_Izz = getGlobal(L, "Izz");
    if (lua_Izz.isNil()) {
        std::cout << "Izz not found!" << std::endl;
    }
    this->Izz = lua_Izz.cast<double>();

    LuaRef lua_Ixy (L, new double);
    lua_Ixy = getGlobal(L, "Ixy");
    if (lua_Ixy.isNil()) {
        std::cout << "Ixy not found!" << std::endl;
    }
    this->Ixy = lua_Ixy.cast<double>();

    LuaRef lua_Ixz (L, new double);
    lua_Ixz = getGlobal(L, "Ixz");
    if (lua_Ixz.isNil()) {
        std::cout << "Ixz not found!" << std::endl;
    }
    this->Ixz = lua_Ixz.cast<double>();

    LuaRef lua_Iyz (L, new double);
    lua_Iyz = getGlobal(L, "Iyz");
    if (lua_Iyz.isNil()) {
        std::cout << "Iyz not found!" << std::endl;
    }
    this->Iyz = lua_Iyz.cast<double>();

   LuaRef lua_sweep (L, new double);
    lua_sweep = getGlobal(L, "sweep");
    if (lua_sweep.isNil()) {
        std::cout << "sweep not found!" << std::endl;
    }
    this->sweep = lua_sweep.cast<double>();

    LuaRef lua_cone (L, new double);
    lua_cone = getGlobal(L, "cone");
    if (lua_cone.isNil()) {
        std::cout << "cone not found!" << std::endl;
    }
    this->cone = lua_cone.cast<double>();

    LuaRef lua_pitch (L, new double);
    lua_pitch = getGlobal(L, "pitch");
    if (lua_pitch.isNil()) {
        std::cout << "pitch not found!" << std::endl;
    }
    this->pitch = lua_pitch.cast<double>();

    LuaRef lua_xac (L, new double);
    lua_xac = getGlobal(L, "x_ac");
    if (lua_xac.isNil()) {
        std::cout << "x_ac not found!" << std::endl;
    }
    this->x_ac = lua_xac.cast<double>();

    LuaRef lua_vel_init (L, new Vector3);
    lua_vel_init = getGlobal(L, "vel_init");
    if (lua_vel_init.isNil()) {
        std::cout << "vel_init not found!" << std::endl;
    }
    this->vel_init = (lua_vel_init);

    LuaRef lua_pos_init (L, new Vector3);
    lua_pos_init = getGlobal(L, "pos_init");
    if (lua_pos_init.isNil()) {
        std::cout << "pos_init not found!" << std::endl;
    }
    this->pos_init = (lua_pos_init);

    LuaRef lua_omega_init (L, new Vector3);
    lua_omega_init = getGlobal(L, "omega_init");
    if (lua_omega_init.isNil()) {
        std::cout << "omega_init not found!" << std::endl;
    }
    this->omega_init = (lua_omega_init);

    LuaRef lua_euler_init (L, new Vector3);
    lua_euler_init = getGlobal(L, "euler_init");
    if (lua_euler_init.isNil()) {
        std::cout << "euler_init not found!" << std::endl;
    }
    this->euler_init = (lua_euler_init);

    // LuaRef lua_euler_init = getGlobal(L, "euler_init");
    // if (lua_dt.isNil()) {
    //     std::cout << "euler_init not found!" << std::endl;
    // }
    // this->euler_init = lua_euler_init.cast<Vector3>();
}

