#include "Aerodynamics.H"
#include "State.H"

trans_rot calc_aero_forces (State & S, Projectile B, int nFoils){
    Vector3 zero;
    std::vector<double> FA11, FA12, FA13, FA21, FA22, FA23;
    std::vector<double> MA11, MA12, MA13, MA21, MA22, MA23;

    double deta = B.arm_length/(nFoils-1);
    double lift = 0;
    double drag = 0;
    double w = 0;
    double cord = B.cord;

    Vector3 r_ac (B.x_ac, 0.0, 0.0);

    // calculate the forces acting on each 2D cross section
    for (int i2Dfoil = 1; i2Dfoil <= nFoils; i2Dfoil++)
    {
        double eta = i2Dfoil*deta;
        double aoa1 = 0;
        double aoa2 = 0;

        Vector3 r_blade (0, eta, 0);
        Vector3 rvec_blade1 = B.inv_T_blade[0] * r_blade;
        Vector3 rvec_blade2 = B.inv_T_blade[1] * r_blade;
        Vector3 rA1 = r_ac + rvec_blade1;
        Vector3 rA2 = r_ac + rvec_blade2;
        Vector3 blade_v1 = S.vel + cross(S.omega, rA1);
        Vector3 blade_v2 = S.vel + cross(S.omega, rA2);

        blade_v1 = -1*blade_v1;
        Vector3 blade_w1 = B.T_blade[0] * blade_v1;
        double w1 = blade_w1.mag();
        aoa1 = atan(blade_w1[2]/blade_w1[0]);
        double Cl1 = CoeffL(aoa1);
        double Cd1 = CoeffD(aoa1);
        double Cm1 = CoeffM(aoa1);


        blade_v2 = -1*blade_v2;
        Vector3 blade_w2 = B.T_blade[1] * blade_v2;
        double w2 = blade_w2.mag();
        aoa2 = atan(blade_w2[2]/blade_w2[0]);
        double Cl2 = CoeffL(aoa2);
        double Cd2 = CoeffD(aoa2);
        double Cm2 = CoeffM(aoa2);
        
        double lift1 = 0.5*1.225*w1*w1*cord*Cl1;
        double drag1 = 0.5*1.225*w1*w1*cord*Cd1;
        double m1 = 0.5*1.225*w1*w1*cord*Cm1;

        double lift2 = 0.5*1.225*w2*w2*cord*Cl2;
        double drag2 = 0.5*1.225*w2*w2*cord*Cd2;
        double m2 = 0.5*1.225*w2*w2*cord*Cm2;

        FA11.push_back(-lift1*sin(aoa1) + drag1*cos(aoa1));
        FA12.push_back(0);
        FA13.push_back(lift1*cos(aoa1) + drag1*sin(aoa1));

        FA21.push_back(-lift2*sin(aoa2) + drag2*cos(aoa2));
        FA22.push_back(0);
        FA23.push_back(lift2*cos(aoa2) + drag2*sin(aoa2));

        MA11.push_back( (lift1*cos(aoa1)+drag1*sin(aoa1))*eta );
        MA12.push_back(m1);
        MA13.push_back((lift1*sin(aoa1) - drag1*cos(aoa1))*eta);

        MA21.push_back( (lift2*cos(aoa2)+drag2*sin(aoa2))*eta );
        MA22.push_back(m2);
        MA23.push_back((lift2*sin(aoa2) - drag2*cos(aoa2))*eta);

    }

    // integrate forces along each blade
    Vector3 FA1 (trap_int(FA11, deta), trap_int(FA12, deta), trap_int(FA13, deta));
    Vector3 FA2 (trap_int(FA21, deta), trap_int(FA22, deta), trap_int(FA23, deta));
    Vector3 FA = B.inv_T_blade[0] * FA1 + B.inv_T_blade[1] * FA2;

    // integrate moments along each blade
    Vector3 MA1 (trap_int(MA11, deta), trap_int(MA12, deta), trap_int(MA13, deta));
    Vector3 MA2 (trap_int(MA21, deta), trap_int(MA22, deta), trap_int(MA23, deta));
    
    // reconstruct overall moment from each discrete moment
    Vector3 temp1 = B.inv_T_blade[0]*FA1;
    Vector3 temp2 = B.inv_T_blade[1]*FA2;
    Vector3 MA = B.inv_T_blade[0] * MA1 + cross(r_ac, temp1)
                + B.inv_T_blade[1] * MA2 + cross(r_ac, temp2);
    //FA1.print(false); FA2.print();
    return trans_rot {FA, MA};
}

double CoeffL(double aoa){
    aoa = aoa * 180 / 3.14159265;
    while (aoa < -180){
        aoa += 360;
    }
    while (aoa > 180){
        aoa -= 360;
    }

    if (aoa <= 10 && aoa >= -10) {
        return 0.1*aoa;
    }
    else if (aoa >= 10 && aoa <= 60){
        return 1.0;
    }
    else if (aoa <= -10 && aoa >= -60){
        return -1.0;
    }
    else if (aoa >= 60 && aoa <= 120){
        return 1-(2.0/60.0)*(aoa-60);
    }
    else if (aoa <= -60 && aoa >= -120){
        return 1-(2.0/60.0)*(aoa+127.5);
    }
    else if (aoa >= 120 && aoa <= 170){
        return -1;
    }
    else if (aoa <= -120 && aoa >= -170){
        return 1;
    }
    else if (aoa >= 170 && aoa <= 180){
        return -1+0.1*(aoa-170);
    }
    else if (aoa <= -170 && aoa >= -180){
        return 0.1*(aoa+180);
    }
}

double CoeffD (double  aoa){
    aoa = aoa * 180 / 3.14159265;
    while (aoa < -180){
        aoa += 360;
    }
    while (aoa > 180){
        aoa -= 360;
    }
    aoa = abs(aoa);
    if (aoa <= 10 ){
        return 0.1;
    }
    else if (aoa >= 10 && aoa <= 90){
        return 0.017*(aoa-10)+0.1;
    }
    else if (aoa >= 90 && aoa <= 170){
        return 1.46-0.017*(aoa-90);
    }
    else if (aoa >= 170 && aoa <= 180){
        return 0.1;
    }
}

double CoeffM (double  aoa){
    aoa = aoa * 180 / 3.14159265;
    while (aoa < -180){
        aoa += 360;
    }
    while (aoa > 180){
        aoa -= 360;
    }
    if (aoa <= 90 && aoa >= -90){
        return -0.00444*aoa;
    }
    if (aoa >= 90 && aoa <= 150){
        return -0.4;
    }
    if (aoa <= 90 && aoa >=-150){
        return 0.4;
    }
    if (aoa <= 180 && aoa >= 150){
        return 0.013333*(aoa-150)-0.4;
    }
    if (aoa <= -150 && aoa >= -180){
        return 0.013333*(aoa+150)+0.4;
    }
}

double trap_int (std::vector<double> integrands, double dx){
    long unsigned int npoints = integrands.size();
    double myIntegral = integrands[0];
    for (int i = 1; i < npoints-1; i++){
        myIntegral += 2*integrands[i];
    }
    myIntegral += integrands.back();
    return myIntegral * dx/2;
}