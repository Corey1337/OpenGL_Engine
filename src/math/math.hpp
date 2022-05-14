#pragma once

#include "mat.hpp"
#include "vec.hpp"

#include <iostream>

#define _USE_MATH_DEFINES

using Mat2 = Matrix<2, 2>;
using Mat3 = Matrix<3, 3>;
using Mat4 = Matrix<4, 4>;

inline float radians(float degree){
    return M_PI * degree / 180.0f;
}

inline float dot_product(Vector2 v1, Vector2 v2){
    return v1.x * v2.x + v1.y * v2.y;
}

inline float length(Vector2 v){
    return sqrtf(powf(v.x, 2) + powf(v.y, 2));
}

inline Vector2 normalize(Vector2 v){
    float lth = length(v); 
    if(lth == 0){
        std::cout << "vector length = 0 cannot be normalized";
        return Vector2(1.0f);
    }
    return v / lth;
}

inline Vector2 reverse(Vector2 v){
    return operator-(v);
}

inline Vector2 distance(Vector2 v1, Vector2 v2){
    return length(v2-v1);
}

inline Vector2 operator*(Mat2 m, Vector2 v) {
    Vector2 out;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            out[i] += m[i][j] * v[j];
    return out;
}

inline float dot_product(Vector3 v1, Vector3 v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float length(Vector3 v){
    return sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
}

inline Vector3 cross_product(Vector3 v1, Vector3 v2){
    Vector3 out;
    out.x = v1.y * v2.z - v1.z * v2.y;
    out.y = v1.z * v2.x - v1.x * v2.z;
    out.z = v1.x * v2.y - v1.y * v2.x;

    return out;
}

inline Vector3 normalize(Vector3 v){
    float lth = length(v); 
    if(lth == 0){
        std::cout << "vector length = 0 cannot be normalized";
        return Vector3(1.0f);
    }
    return v / lth;
}

inline Vector3 reverse(Vector3 v){
    return operator-(v);
}

inline Vector3 distance(Vector3 v1, Vector3 v2){
    return length(v2-v1);
}

inline Vector3 operator*(Mat3 m, Vector3 v) {
    Vector3 out;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            out[i] += m[i][j] * v[j];
    return out;
}

inline float dot_product(Vector4 v1, Vector4 v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline float length(Vector4 v){
    return sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2) + powf(v.w, 2));
}

inline Vector4 normalize(Vector4 v){
    float lth = length(v); 
    if(lth == 0){
        std::cout << "vector length = 0 cannot be normalized";
        return Vector4(1.0f);
    }
    return v / lth;
}

inline Vector4 reverse(Vector4 v){
    return operator-(v);
}

inline Vector4 distance(Vector4 v1, Vector4 v2){
    return length(v2-v1);
}

inline Vector4 operator*(Mat4 m, Vector4 v) {
    Vector4 out;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            out[i] += m[i][j] * v[j];
    return out;
}

template<int M>
inline Matrix<M, M> identity(Matrix<M, M> m, float f = 1.0f){
    Matrix<M, M> out;
    for (int i = 0; i < M; i++){
        out[i][i] = f;
    }
    return out;
}

template<int M, int N>
inline Matrix<M, N> transpose(Matrix<M, N> m) {
    Matrix<N, M> out;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            out[i][j] = m[j][i];
    return out;
}

inline float det(Mat2 m) {
    return (m[0][0]*m[1][1]
            -m[0][1]*m[1][0]);
}

inline float det(Mat3 m) {
    return (m[0][0]*m[1][1]*m[2][2] 
            + m[0][1]*m[1][2]*m[2][0] 
            + m[0][2]*m[1][0]*m[2][1] 
            - m[0][2]*m[1][1]*m[2][0]
            - m[0][0]*m[1][2]*m[2][1] 
            - m[0][1]*m[1][0]*m[2][2]);
}

inline Mat2 adj(Mat2 m){
    Mat2 out;
    out[0][0] = m[1][1];
    out[0][1] = -m[1][0];
    out[1][0] = -m[0][1];
    out[1][1] = m[0][0];
    return out;
}

inline Mat3 adj(Mat3 m) {
    Mat3 out;
    out[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    out[0][1] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]);
    out[0][2] = m[1][0] * m[2][1] - m[2][0] * m[1][1];
    out[1][0] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]);
    out[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
    out[1][2] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]);
    out[2][0] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
    out[2][1] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]);
    out[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    return out;
}

inline Mat4 inverse(Mat4 m_) {
    Mat4 m = transpose(m_);
    float SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    float SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    float SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    float SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    float SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    float SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
    float SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
    float SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    float SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
    float SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
    float SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
    float SubFactor11 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
    float SubFactor12 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
    float SubFactor13 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
    float SubFactor14 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
    float SubFactor15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
    float SubFactor16 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
    float SubFactor17 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

    Mat4 Inverse;
    Inverse[0][0] = +(m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02);
    Inverse[0][1] = -(m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04);
    Inverse[0][2] = +(m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05);
    Inverse[0][3] = -(m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05);

    Inverse[1][0] = -(m[0][1] * SubFactor00 - m[0][2] * SubFactor01 + m[0][3] * SubFactor02);
    Inverse[1][1] = +(m[0][0] * SubFactor00 - m[0][2] * SubFactor03 + m[0][3] * SubFactor04);
    Inverse[1][2] = -(m[0][0] * SubFactor01 - m[0][1] * SubFactor03 + m[0][3] * SubFactor05);
    Inverse[1][3] = +(m[0][0] * SubFactor02 - m[0][1] * SubFactor04 + m[0][2] * SubFactor05);

    Inverse[2][0] = +(m[0][1] * SubFactor06 - m[0][2] * SubFactor07 + m[0][3] * SubFactor08);
    Inverse[2][1] = -(m[0][0] * SubFactor06 - m[0][2] * SubFactor09 + m[0][3] * SubFactor10);
    Inverse[2][2] = +(m[0][0] * SubFactor07 - m[0][1] * SubFactor09 + m[0][3] * SubFactor11);
    Inverse[2][3] = -(m[0][0] * SubFactor08 - m[0][1] * SubFactor10 + m[0][2] * SubFactor11);

    Inverse[3][0] = -(m[0][1] * SubFactor12 - m[0][2] * SubFactor13 + m[0][3] * SubFactor14);
    Inverse[3][1] = +(m[0][0] * SubFactor12 - m[0][2] * SubFactor15 + m[0][3] * SubFactor16);
    Inverse[3][2] = -(m[0][0] * SubFactor13 - m[0][1] * SubFactor15 + m[0][3] * SubFactor17);
    Inverse[3][3] = +(m[0][0] * SubFactor14 - m[0][1] * SubFactor16 + m[0][2] * SubFactor17);

    float Determinant =
        + m[0][0] * Inverse[0][0]
        + m[0][1] * Inverse[0][1]
        + m[0][2] * Inverse[0][2]
        + m[0][3] * Inverse[0][3];

    Inverse = Inverse * (1.0f / Determinant);

    return Inverse;
}

template<int M>
inline Matrix<M, M> inverse(Matrix<M, M> m) {
    float det__ = det(m);
    if(det__){
        return (1/det__) * adj(transpose(m));
    }
    else
        return m;
}

// inline Mat3 translation(Vector2 v){
//     Mat3 trans;
//     trans[0][0] = 1;
//     trans[1][1] = 1;
//     trans[2][2] = 1;
//     trans[0][2] = v.x;
//     trans[1][2] = v.y;
//     return trans;
// }

inline Mat4 translationMat(Vector3 v){
    Mat4 trans;
    trans[0][0] = 1;
    trans[1][1] = 1;
    trans[2][2] = 1;
    trans[3][3] = 1;
    trans[0][3] = v.x;
    trans[1][3] = v.y;
    trans[2][3] = v.z;

    return transpose(trans);
}

// inline Mat3 scale(Vector2 v){
//     Mat3 trans;
//     trans[0][0] = v.x;
//     trans[1][1] = v.y;
//     trans[2][2] = 1;
//     return trans;
// }

inline Mat4 scaleMat(Vector3 v){
    Mat4 scale;
    scale[0][0] = v.x;
    scale[1][1] = v.y;
    scale[2][2] = v.z;
    scale[3][3] = 1;
    return scale;
}

// inline Mat3 rotate(float angle){
//     Mat3 rot;
//     float sin_a = sinf(angle);
//     float cos_a = cosf(angle);
//     rot[0][0] = cos_a;
//     rot[0][1] = sin_a;
//     rot[1][0] = -sin_a;
//     rot[1][1] = cos_a;
// }

inline Mat4 rotateMat(float a, float b, float g){
    float sa = sinf(a);
    float ca = cosf(a);
    float sb = sinf(b);
    float cb = cosf(b);
    float sg = sinf(g);
    float cg = cosf(g);
    Mat4 rot = {
        {ca*cg-sa*cb*sg, -ca*sg-sa*cb+cg, sa*sb, 0.0f},
        {sa*cg+ca*cb*sg, -sa*sg+ca*cb*cg, -ca*sb, 0.0f},
        {sb*sg, sb*cg, cb, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    return rot;
}

inline Mat4 rotateMat(Vector3 v, float a) {
        if(length(v) == 0)
            return identity(Mat4(0));
		Vector3 R = normalize(v);
		float c = cosf(a);
		float s = sinf(a);

		Mat4 rot = {
		    { c + R.x * R.x * (1 - c), R.x * R.y * (1 - c) - R.z * s, R.x * R.z * (1 - c) + R.y * s, 0 },
			{ R.y * R.x * (1 - c) + R.z * s, c + R.y * R.y * (1 - c), R.y * R.z * (1 - c) - R.x * s, 0 },
			{ R.z * R.x * (1 - c) - R.y * s, R.z * R.y * (1 - c) + R.x * s, c + R.z * R.z * (1 - c), 0 },
			{ 0, 0, 0, 1 }
		};
		return transpose(rot);
}

inline Mat4 CraeteModelMatrix(Mat4 translation_Matrix, Mat4 rotation_Matrix, Mat4 scale_Matrix){
    return translation_Matrix*rotation_Matrix*scale_Matrix;
}

inline Mat4 CreateViewMatrix(Vector3 from, Vector3 to, Vector3 worldUp){
    Vector3 forward = normalize(to - from);
    Vector3 right = normalize(cross_product(forward, worldUp));
    Vector3 up = normalize(cross_product(right, forward));
    Mat4 view = {
        {right.x, up.x, -forward.x, 0},
        {right.y, up.y, -forward.y, 0},
        {right.z, up.z, -forward.z, 0},
        {-dot_product(right, from), -dot_product(up, from), dot_product(forward, from), 1}
    };
    return view;
}

inline Mat4 ortho(float left, float right, float bottom, float top, float near, float far){
    Mat4 ort;
    ort[0][0] = 2/(right - left);
    ort[1][1] = 2/(top - bottom);
    ort[2][2] = -2/(far - near);
    ort[3][0] = -(right + left)/(right - left);
    ort[3][1] = -(top + bottom)/(top - bottom);
    ort[3][2] = -(far + near)/(far - near);
    ort[3][3] = 1;
    return ort;
}

inline Mat4 perspective(float fov, float aspect, float near, float far){
    Mat4 perspect;
    float tfov = tanf(fov/2);
    perspect[0][0] = 1/(tfov * aspect);
    perspect[1][1] = 1/tfov;
    perspect[2][2] = -(far + near)/(far-near);
    perspect[2][3] = -1;
    perspect[3][2] = -2*far*near/(far - near);
    return perspect;
}