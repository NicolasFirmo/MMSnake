#pragma once

template <typename T>
struct Matrix4 {
	T e[4 * 4]{0};

	[[nodiscard]] constexpr Matrix4 operator+(const Matrix4& other) const {
		Matrix4 res;
		for (size_t i = 0; i < std::size(e); i++) res[i] = e[i] + other[i];
		return res;
	}

	[[nodiscard]] constexpr Matrix4 operator-(const Matrix4& other) const {
		Matrix4 res;
		for (size_t i = 0; i < std::size(e); i++) res[i] = e[i] - other[i];
		return res;
	}
	[[nodiscard]] constexpr Matrix4 operator*(const T& value) const {
		Matrix4 res;
		for (size_t i = 0; i < std::size(e); i++) res[i] = e[i] * value;
		return res;
	}
};

template <typename T>
constexpr Matrix4<T> operator*(const T& value, const Matrix4<T>& matrix) {
	Matrix4<T> res;
	for (size_t i = 0; i < std::size(matrix.e); i++) res[i] = matrix.e[i] * value;
	return res;
}