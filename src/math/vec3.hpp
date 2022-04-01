#include <vector>
#include <cmath>

struct Vector3
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    Vector3(){

    }

    Vector3(float f){
        this->x = f;
        this->y = f;
        this->z = f;
    }

    Vector3(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    inline float& operator[](int index){
        return *(&x + index);
    }

    inline const float& operator[](int index)const{
        return *(&x + index);
    }

    Vector3& operator=(Vector3 right){
        x = right.x;
        y = right.y;
        z = right.z;
        return *this;
    }

    Vector3& operator+=(Vector3 right){
        x += right.x;
        y += right.y;
        z += right.z;
        return *this;
    }

    Vector3& operator-=(Vector3 right){
        x -= right.x;
        y -= right.y;
        z -= right.z;
        return *this;
    }

};

inline bool operator==(Vector3 v1, Vector3 v2){
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

inline bool operator!=(Vector3 v1, Vector3 v2){
    return !operator==(v1, v2);
}

inline Vector3 operator+(Vector3 v1, Vector3 v2){
    return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector3 operator-(Vector3 v1, Vector3 v2){
    return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vector3 operator-(Vector3 v){
    return Vector3(v.x * -1, v.y * -1, v.z * -1);
}

inline Vector3 operator*(Vector3 v1, Vector3 v2){
    return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline Vector3 operator*(Vector3 v, float f){
    return Vector3(v.x * f, v.y * f, v.z * f);
}

inline Vector3 operator*(float f, Vector3 v){
    return operator*(v, f);
}

inline Vector3 operator/(Vector3 v, float f){
    return Vector3(v.x / f, v.y / f, v.z / f);
}

inline float dot_product(Vector3 v1, Vector3 v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float lenth(Vector3 v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

inline Vector3 cross_product(Vector3 v1, Vector3 v2){
    Vector3 out;
    out.x = v1.y * v2.z - v1.z * v2.y;
    out.y = v1.z * v2.x - v1.x * v2.z;
    out.z = v1.x * v2.y - v1.y * v2.x;

    return out;
}

inline Vector3 normalize(Vector3 v){
    return v / lenth(v);
}

inline Vector3 reverse(Vector3 v){
    return operator-(v);
}

inline Vector3 distance(Vector3 v1, Vector3 v2){
    return lenth(v2-v1);
}