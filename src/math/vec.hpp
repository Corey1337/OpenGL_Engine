#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>
#include <array>
#include <ostream>

#include "glm/glm.hpp"

struct Vector2
{
    float x = 0.0;
    float y = 0.0;

    Vector2(){}

    Vector2(float f)
    {
        this->x = f;
        this->y = f;
    }

    Vector2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    inline float &operator[](int index)
    {
        return *(&x + index);
    }

    inline const float &operator[](int index) const
    {
        return *(&x + index);
    }

    inline Vector2 &operator=(Vector2 right)
    {
        x = right.x;
        y = right.y;
        return *this;
    }

    inline Vector2 &operator+=(Vector2 right)
    {
        x += right.x;
        y += right.y;
        return *this;
    }

    inline Vector2 &operator-=(Vector2 right)
    {
        x -= right.x;
        y -= right.y;
        return *this;
    }

    glm::vec2 ToGLMVec()
    {
        return glm::vec2(this->x, this->y);
    }
    // TODO:
    // Vector2(std::initializer_list<float> init) {
    //     if (init.size() != 2) {
    //         throw std::invalid_argument("Vector size must be the same");
    //     }

    //     for (int i = 0; i < 2; i++) {
    //         this[i] = *(init.begin() + i);
    //     }
    // }
};

inline bool operator==(Vector2 v1, Vector2 v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

inline bool operator!=(Vector2 v1, Vector2 v2)
{
    return !operator==(v1, v2);
}

inline Vector2 operator+(Vector2 v1, Vector2 v2)
{
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

inline Vector2 operator-(Vector2 v1, Vector2 v2)
{
    return Vector2(v1.x - v2.x, v1.y - v2.y);
}

inline Vector2 operator-(Vector2 v)
{
    return Vector2(v.x * -1, v.y * -1);
}

inline Vector2 operator*(Vector2 v1, Vector2 v2)
{
    return Vector2(v1.x * v2.x, v1.y * v2.y);
}

inline Vector2 operator*(Vector2 v, float f)
{
    return Vector2(v.x * f, v.y * f);
}

inline Vector2 operator*(float f, Vector2 v)
{
    return operator*(v, f);
}

inline Vector2 operator/(Vector2 v, float f)
{
    return Vector2(v.x / f, v.y / f);
}

struct Vector3
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    Vector3()
    {
    }

    Vector3(float f)
    {
        this->x = f;
        this->y = f;
        this->z = f;
    }

    Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    inline float &operator[](int index)
    {
        return *(&x + index);
    }

    inline const float &operator[](int index) const
    {
        return *(&x + index);
    }

    inline Vector3 &operator=(Vector3 right)
    {
        x = right.x;
        y = right.y;
        z = right.z;
        return *this;
    }

    inline Vector3 &operator+=(Vector3 right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        return *this;
    }

    inline Vector3 &operator-=(Vector3 right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        return *this;
    }

    glm::vec3 ToGLMVec()
    {
        return glm::vec3(this->x, this->y, this->z);
    }
};

inline bool operator==(Vector3 v1, Vector3 v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

inline bool operator!=(Vector3 v1, Vector3 v2)
{
    return !operator==(v1, v2);
}

inline Vector3 operator+(Vector3 v1, Vector3 v2)
{
    return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector3 operator-(Vector3 v1, Vector3 v2)
{
    return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vector3 operator-(Vector3 v)
{
    return Vector3(v.x * -1, v.y * -1, v.z * -1);
}

inline Vector3 operator*(Vector3 v1, Vector3 v2)
{
    return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline Vector3 operator*(Vector3 v, float f)
{
    return Vector3(v.x * f, v.y * f, v.z * f);
}

inline Vector3 operator*(float f, Vector3 v)
{
    return operator*(v, f);
}

inline Vector3 operator/(Vector3 v, float f)
{
    return Vector3(v.x / f, v.y / f, v.z / f);
}

struct Vector4
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    float w = 0.0;

    Vector4()
    {
    }

    Vector4(float f)
    {
        this->x = f;
        this->y = f;
        this->z = f;
        this->w = f;
    }

    Vector4(float x, float y, float z, float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    inline float &operator[](int index)
    {
        return *(&x + index);
    }

    inline const float &operator[](int index) const
    {
        return *(&x + index);
    }

    inline Vector4 &operator=(Vector4 right)
    {
        x = right.x;
        y = right.y;
        z = right.z;
        w = right.w;
        return *this;
    }

    inline Vector4 &operator+=(Vector4 right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        w += right.w;
        return *this;
    }

    inline Vector4 &operator-=(Vector4 right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        w -= right.w;
        return *this;
    }
    glm::vec4 ToGLMVec()
    {
        return glm::vec4(this->x, this->y, this->z, this->w);
    }
};

inline bool operator==(Vector4 v1, Vector4 v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

inline bool operator!=(Vector4 v1, Vector4 v2)
{
    return !operator==(v1, v2);
}

inline Vector4 operator+(Vector4 v1, Vector4 v2)
{
    return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

inline Vector4 operator-(Vector4 v1, Vector4 v2)
{
    return Vector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

inline Vector4 operator-(Vector4 v)
{
    return Vector4(v.x * -1, v.y * -1, v.z * -1, v.w * -1);
}

inline Vector4 operator*(Vector4 v1, Vector4 v2)
{
    return Vector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

inline Vector4 operator*(Vector4 v, float f)
{
    return Vector4(v.x * f, v.y * f, v.z * f, v.w * f);
}

inline Vector4 operator*(float f, Vector4 v)
{
    return operator*(v, f);
}

inline Vector4 operator/(Vector4 v, float f)
{
    return Vector4(v.x / f, v.y / f, v.z / f, v.w / f);
}