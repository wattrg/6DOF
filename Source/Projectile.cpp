#include "Projectile.H"


Matrix3 Projectile::Tj (double sweep, double cone, double pitch){
    double Tj_array[3][3] = {
        sin(sweep)*cos(pitch) + cos(sweep)*sin(cone)*sin(pitch), 
        -cos(sweep)*cos(pitch) + sin(sweep)*sin(cone)*sin(pitch), 
        -cos(cone)*sin(pitch),

        -cos(sweep)*cos(cone),
        sin(sweep)*cos(cone), 
        sin(cone),

        sin(sweep)*sin(pitch) - cos(sweep)*sin(cone)*cos(pitch),
        -cos(sweep)*sin(pitch) - sin(sweep)*sin(cone)*cos(pitch), 
        cos(cone)*cos(pitch)
    };
    return Matrix3(Tj_array);
}

