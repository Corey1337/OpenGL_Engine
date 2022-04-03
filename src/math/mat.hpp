#pragma once

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