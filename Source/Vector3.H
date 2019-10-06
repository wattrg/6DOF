#include <vector>
#include <cmath>
#include <assert.h>
#include <iostream>

#ifndef Vector3_H
#define Vector3_H

class Vector3 {
    private:
        std::vector<double> vec;
    public:
        
        Vector3 (){
            vec = {0.0, 0.0, 0.0};
        };
        Vector3 (double a, double b, double c){
            vec = {a, b, c};
        };


        void print(bool end_line=true){
            std::cout << "[" << vec[0] << ", " << vec[1] << ", " << vec[2] << "]";
            if (end_line){
                std::cout << std::endl;
            }
        };
        double mag (){
            return sqrt(vec[0]*vec[0] + vec[2]*vec[2]);
        };
        double & operator [] (size_t i){
            assert (i >= 0 && i <=2);
            return vec[i];
        };

        int len(){
            return vec.size();
        }

};

Vector3 operator * (double alpha, Vector3 a);
Vector3 cross (Vector3 a, Vector3 b);
Vector3 operator + (Vector3 a, Vector3 b);
Vector3 operator - (Vector3 a, Vector3 b);


#endif