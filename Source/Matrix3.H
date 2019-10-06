#include <vector>
#include "Vector3.H"
#include <cmath>
#include <assert.h>
#include <iostream>

#ifndef Matrix3_H
#define Matrix3_H

class Matrix3 {
    private:
        std::vector<Vector3> mat;
    public:
        
        Matrix3 () {
            Vector3 zero;
            mat = {zero, zero, zero};
        };

        Matrix3 (Vector3 a, Vector3 b, Vector3 c){
            mat = {a, b, c};
        };

        Matrix3 (double matrix[3][3]){
            Vector3 row0 = {matrix[0][0], matrix[0][1], matrix[0][2]};
            Vector3 row1 = {matrix[1][0], matrix[1][1], matrix[1][2]};
            Vector3 row2 = {matrix[2][0], matrix[2][1], matrix[2][2]};
            mat = {row0, row1, row2};
        };

        Vector3 & operator [] (size_t i){
           assert (i >= 0 && i <= 2);
           return mat[i];
        };

        void print(){
            std::cout << "[";
            for (int i = 0; i <= 1; i++){
                mat[i].print();
            }
            mat[2].print(false);
            std::cout << "]" << std::endl;
        }; 

        double det (){
            double det = 0;
            for (int i = 0; i < 3; i++){
                det = det + (mat[0][i] * (mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3] * mat[2][(i+1)%3]));
            }
            return det;
        };

        Matrix3 T (){
            Matrix3 transpose;
            for (int i=0; i < 3; i++){
                for (int j=0; j < 3; j++){
                    transpose[i][j] = mat[j][i];
                }
            }
            return transpose;
        };

        Matrix3 inv (){
            Matrix3 invMat;
            double determinent = det();
            for(int i = 0; i < 3; i++){
		        for(int j = 0; j < 3; j++){
			        invMat[i][j] = ((mat[(j+1)%3][(i+1)%3] * mat[(j+2)%3][(i+2)%3]) 
                    - (mat[(j+1)%3][(i+2)%3] * mat[(j+2)%3][(i+1)%3])) / determinent;
                }
	        }
            return invMat;
        };
    };

Matrix3 operator * (Matrix3 & a, Matrix3 & b);
Vector3 operator * (Matrix3 & M, Vector3 & V);

#endif