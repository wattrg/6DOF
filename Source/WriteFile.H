#include <fstream>
#include <iostream>
#include "State.H"


#ifndef writeFile_h
#define writeFile_h

void write_file (std::ofstream& outfile, State& S, double & time);

#endif