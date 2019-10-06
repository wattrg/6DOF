#!/bin/sh

g++ ../Source/main.cpp ../Source/Matrix3.cpp ../Source/Vector3.cpp        \
../Source/Projectile.cpp ../Source/DOF6.cpp ../Source/TimeIntegration.cpp \
../Source/WriteFile.cpp ../Source/ParmParse.cpp  ../Source/State.cpp      \
../Source/Aerodynamics.cpp  -o sixDOF.ex                                  \
-I ../lua-5.3.5/src/ -I ../LuaBridge/Source/LuaBridge/                    \
-I ../LuaBridge/Source/ -L ../lua-5.3.5/src/ -llua -ldl -g
