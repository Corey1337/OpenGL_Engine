#include <vector>
#include <cmath>

struct Vector4
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    float w = 0.0;

    Vector4(){

    }

    Vector4(float f){
        this->x = f;
        this->y = f;
        this->z = f;
        this->w = f;
    }

    Vector4(float x, float y, float z, float w){
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    
    inline float& operator[](int index){
        return *(&x + index);
    }

    inline const float& operator[](int index)const{
        return *(&x + index);
    }

    Vector4& operator=(Vector4 right){
        x = right.x;
        y = right.y;
        z = right.z;
        w = right.w;
        return *this;
    }

    Vector4& operator+=(Vector4 right){
        x += right.x;
        y += right.y;
        z += right.z;
        w += right.w;
        return *this;
    }

    Vector4& operator-=(Vector4 right){
        x -= right.x;
        y -= right.y;
        w -= right.w;
        z -= right.z;
        return *this;
    }

};

bool operator==(Vector4 v1, Vector4 v2){
    return v1.x==v2.x && v1.y==v2.y && v1.z==v2.z && v1.w==v2.w;
}

bool operator!=(Vector4 v1, Vector4 v2){
    return !operator==(v1, v2);
}

Vector4 operator+(Vector4 v1, Vector4 v2){
    return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

Vector4 operator-(Vector4 v1, Vector4 v2){
    return Vector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

Vector4 operator-(Vector4 v){
    return Vector4(v.x * -1, v.y * -1, v.z * -1, v.w * -1);
}

Vector4 operator*(Vector4 v1, Vector4 v2){
    return Vector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

Vector4 operator*(Vector4 v, float f){
    return Vector4(v.x * f, v.y * f, v.z * f, v.w * f);
}

Vector4 operator*(float f, Vector4 v){
    return operator*(v, f);
}

Vector4 operator/(Vector4 v, float f){
    return Vector4(v.x / f, v.y / f, v.z / f, v.w / f);
}

float dot_product(Vector4 v1, Vector4 v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

float lenth(Vector4 v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) + pow(v.w, 2));
}

Vector4 normalize(Vector4 v){
    return v / lenth(v);
}

Vector4 reverse(Vector4 v){
    return operator-(v);
}

Vector4 distance(Vector4 v1, Vector4 v2){
    return lenth(v2-v1);
}