#include "WriteFile.H"
#include "State.H"

void write_file (std::ofstream& out, State& S, double & time){
    out << time << ",";
    for (int i = 0; i < 3; i++){
        out << S.vel[i] << ",";
    }
    for (int i = 0; i < 3; i++){
        out << S.euler[i] << ",";
    }
    for (int i = 0; i < 3; i++){
        out << S.omega[i] << ",";
    }
    for (int i = 0; i < 3; i++){
        out << S.inert_vel[i] << ",";
    }
    for (int i = 0; i < 2; i++){
        out << S.inert_pos[i] << ",";
    }

    out << S.inert_pos[2] << std::endl;
}