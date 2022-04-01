#include <vector>
#include <cmath>

struct Vector2
{
    float x = 0.0;
    float y = 0.0;

    Vector2(){

    }

    Vector2(float f){
        this->x = f;
        this->y = f;
    }

    Vector2(float x, float y){
        this->x = x;
        this->y = y;
    }

    Vector2& operator=(Vector2 right){
        x = right.x;
        y = right.y;
        return *this;
    }

    Vector2& operator+=(Vector2 right){
        x += right.x;
        y += right.y;
        return *this;
    }

    Vector2& operator-=(Vector2 right){
        x -= right.x;
        y -= right.y;
        return *this;
    }

};

bool operator==(Vector2 v1, Vector2 v2){
    return v1.x==v2.x && v1.y==v2.y;
}

bool operator!=(Vector2 v1, Vector2 v2){
    return !operator==(v1, v2);
}

Vector2 operator+(Vector2 v1, Vector2 v2){
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2 operator-(Vector2 v1, Vector2 v2){
    return Vector2(v1.x - v2.x, v1.y - v2.y);
}

Vector2 operator-(Vector2 v){
    return Vector2(v.x * -1, v.y * -1);
}

Vector2 operator*(Vector2 v1, Vector2 v2){
    return Vector2(v1.x * v2.x, v1.y * v2.y);
}

Vector2 operator*(Vector2 v, float f){
    return Vector2(v.x * f, v.y * f);
}

Vector2 operator*(float f, Vector2 v){
    return operator*(v, f);
}

Vector2 operator/(Vector2 v, float f){
    return Vector2(v.x / f, v.y / f);
}

float dot(Vector2 v1, Vector2 v2){
    return v1.x * v2.x + v1.y * v2.y;
}

float lenth(Vector2 v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

Vector2 normalize(Vector2 v){
    return v / lenth(v);
}

Vector2 reverse(Vector2 v){
    return operator-(v);
}