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

    inline float& operator[](int index){
        return *(&x + index);
    }

    inline const float& operator[](int index)const{
        return *(&x + index);
    }

    inline Vector2& operator=(Vector2 right){
        x = right.x;
        y = right.y;
        return *this;
    }

    inline Vector2& operator+=(Vector2 right){
        x += right.x;
        y += right.y;
        return *this;
    }

    inline Vector2& operator-=(Vector2 right){
        x -= right.x;
        y -= right.y;
        return *this;
    }
};

inline bool operator==(Vector2 v1, Vector2 v2){
    return v1.x==v2.x && v1.y==v2.y;
}

inline bool operator!=(Vector2 v1, Vector2 v2){
    return !operator==(v1, v2);
}

inline Vector2 operator+(Vector2 v1, Vector2 v2){
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

inline Vector2 operator-(Vector2 v1, Vector2 v2){
    return Vector2(v1.x - v2.x, v1.y - v2.y);
}

inline Vector2 operator-(Vector2 v){
    return Vector2(v.x * -1, v.y * -1);
}

inline Vector2 operator*(Vector2 v1, Vector2 v2){
    return Vector2(v1.x * v2.x, v1.y * v2.y);
}

inline Vector2 operator*(Vector2 v, float f){
    return Vector2(v.x * f, v.y * f);
}

inline Vector2 operator*(float f, Vector2 v){
    return operator*(v, f);
}

inline Vector2 operator/(Vector2 v, float f){
    return Vector2(v.x / f, v.y / f);
}

inline float dot_product(Vector2 v1, Vector2 v2){
    return v1.x * v2.x + v1.y * v2.y;
}

inline float lenth(Vector2 v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

inline Vector2 normalize(Vector2 v){
    return v / lenth(v);
}

inline Vector2 reverse(Vector2 v){
    return operator-(v);
}

inline Vector2 distance(Vector2 v1, Vector2 v2){
    return lenth(v2-v1);
}