
#include "Vector3.H"
#include <assert.h>


Vector3 cross (Vector3 a, Vector3 b){
    Vector3 v_cross;
    v_cross[0] = a[1]*b[2] - a[2]*b[1];
    v_cross[1] = a[2]*b[0] - a[0]*b[2];
    v_cross[2] = a[0]*b[1] - a[1]*b[0];
    return v_cross;
}



Vector3 operator * (double alpha, Vector3 a){
    assert(a.len() == 3);
    for (int i = 0; i <=2; i++){
        a[i] = alpha * a[i];
    }
    return a;
}



Vector3 operator + (Vector3 a, Vector3 b){
    assert(a.len() == 3);
    assert(b.len() == 3);

    Vector3 sum;
    for (int i = 0; i < 3; i++){
        sum[i] = a[i] + b[i];
    }
    assert(sum.len() == 3);
    return sum;
};

Vector3 operator - (Vector3 a, Vector3 b){
    assert(a.len() == 3);
    assert(b.len() == 3);
    Vector3 diff;
    for (int i = 0; i < 3; i++){
        diff[i] = a[i] - b[i];
    }
    assert(diff.len() == 3);
    return diff;
};