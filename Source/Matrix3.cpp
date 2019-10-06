#include "Matrix3.H"
#include "Vector3.H"

Matrix3 operator * (Matrix3 & A, Matrix3 & B){
    double prod_array[3][3] = {0., 0., 0.,
                               0., 0., 0.,
                               0., 0., 0.};
    Matrix3 prod (prod_array);
    for (int i=0; i < 3; i++){
        for (int j=0; j < 3; j++){
            for (int n=0; n < 3; n ++){
                prod[i][j] += A[i][n] * B[n][j];
            }
        }
    }
    return prod;
}

Vector3 operator * (Matrix3 & M, Vector3 & V){
    Vector3 prod (0,0,0);
    for (int i=0; i < 3; i++){
        for (int n=0; n < 3; n++){
            prod[i] += M[i][n] * V[n];
        }
    }
    return prod;
}

