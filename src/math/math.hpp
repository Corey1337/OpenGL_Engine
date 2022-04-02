#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>
#include <array>
#include <ostream>


template <int M, int N>
struct Matrix
{
    private:
        std::array<std::array<float, N>, M> data;
    public:
        Matrix() {
            for(int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    data[i][j] = 0;
        }
        Matrix(float f) {
            for(int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    data[i][j] = f;
        }

        inline std::array<float, N>& operator[](const int index) {
             return data[index]; 
        }

		inline const std::array<float, N>& operator[](const int index) const { 
            return data[index];
        }

        Matrix(std::initializer_list<std::initializer_list<float>> init) {
			if (init.size() != M) {
				throw std::invalid_argument("Matrix dimension must be the same");;
			}
            
			for (int i = 0; i < M; i++) {
				if ((init.begin() + i)->size() != N)
					throw;

				for (int j = 0; j < N; j++)
					data[i][j] = *((init.begin() + i)->begin() + j);
			}
		}
};

template<int M, int N>
inline Matrix<M, N> operator+(Matrix<M, N> m1, Matrix<M, N> m2) {
		Matrix<M, N> out;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				out[i][j] = m1[i][j] + m2[i][j];
		return out;
}

template<int M, int N>
inline Matrix<M, N> operator-(Matrix<M, N> m1, Matrix<M, N> m2) {
		Matrix<M, N> out;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				out[i][j] = m1[i][j] - m2[i][j];
		return out;
}

template<int M, int N>
inline Matrix<M, N> operator*(Matrix<M, N> m1, float f) {
		Matrix<M, N> out;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				out[i][j] = m1[i][j] * f;
		return out;
}

template<int M, int N>
inline Matrix<M, N> operator*(float f, Matrix<M, N> m1) {
		return operator*(m1, f);
}

template<int M>
inline Matrix<M, M> operator*(Matrix<M, M> m1, Matrix<M, M> m2) {
		Matrix<M, M> out;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < M; j++)
				for(int k = 0; k < M; k++)
                    out[i][j] += m1[i][k] * m2[k][j];
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

using Mat2 = Matrix<2, 2>;
using Mat3 = Matrix<3, 3>;
using Mat4 = Matrix<4, 4>;

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

inline float det(Mat4 m) {
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
        +m[0][0] * Inverse[0][0]
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

inline Vector2 operator*(Mat2 m, Vector2 v) {
    Vector2 out;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            out[j] += m[i][j] * v[j];
    return out;
}

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

    inline Vector3& operator=(Vector3 right){
        x = right.x;
        y = right.y;
        z = right.z;
        return *this;
    }

    inline Vector3& operator+=(Vector3 right){
        x += right.x;
        y += right.y;
        z += right.z;
        return *this;
    }

    inline Vector3& operator-=(Vector3 right){
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

inline Vector3 operator*(Mat3 m, Vector3 v) {
    Vector3 out;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            out[j] += m[i][j] * v[j];
    return out;
}

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

    inline Vector4& operator=(Vector4 right){
        x = right.x;
        y = right.y;
        z = right.z;
        w = right.w;
        return *this;
    }

    inline Vector4& operator+=(Vector4 right){
        x += right.x;
        y += right.y;
        z += right.z;
        w += right.w;
        return *this;
    }

    inline Vector4& operator-=(Vector4 right){
        x -= right.x;
        y -= right.y;
        w -= right.w;
        z -= right.z;
        return *this;
    }

};

inline bool operator==(Vector4 v1, Vector4 v2){
    return v1.x==v2.x && v1.y==v2.y && v1.z==v2.z && v1.w==v2.w;
}

inline bool operator!=(Vector4 v1, Vector4 v2){
    return !operator==(v1, v2);
}

inline Vector4 operator+(Vector4 v1, Vector4 v2){
    return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

inline Vector4 operator-(Vector4 v1, Vector4 v2){
    return Vector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

inline Vector4 operator-(Vector4 v){
    return Vector4(v.x * -1, v.y * -1, v.z * -1, v.w * -1);
}

inline Vector4 operator*(Vector4 v1, Vector4 v2){
    return Vector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

inline Vector4 operator*(Vector4 v, float f){
    return Vector4(v.x * f, v.y * f, v.z * f, v.w * f);
}

inline Vector4 operator*(float f, Vector4 v){
    return operator*(v, f);
}

inline Vector4 operator/(Vector4 v, float f){
    return Vector4(v.x / f, v.y / f, v.z / f, v.w / f);
}

inline float dot_product(Vector4 v1, Vector4 v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline float lenth(Vector4 v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) + pow(v.w, 2));
}

inline Vector4 normalize(Vector4 v){
    return v / lenth(v);
}

inline Vector4 reverse(Vector4 v){
    return operator-(v);
}

inline Vector4 distance(Vector4 v1, Vector4 v2){
    return lenth(v2-v1);
}

inline Vector4 operator*(Mat4 m, Vector4 v) {
    Vector4 out;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            out[j] += m[i][j] * v[j];
    return out;
}
