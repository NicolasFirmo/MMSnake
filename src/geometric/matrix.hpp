#pragma once

template <typename T>
struct Matrix4 {
	struct Row {
		T c[4];
	};

	Row r[4];

	[[nodiscard]] constexpr Matrix4 operator+(const Matrix4& other) const {
		Matrix4 res;
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++) res.r[i].c[j] = r[i].c[j] + other.r[i].c[j];
		return res;
	}

	[[nodiscard]] constexpr Matrix4 operator-(const Matrix4& other) const {
		Matrix4 res;
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++) res.r[i].c[j] = r[i].c[j] - other.r[i].c[j];
		return res;
	}
	[[nodiscard]] constexpr Matrix4 operator*(const T& value) const {
		Matrix4 res;
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++) res.r[i].c[j] = r[i].c[j] * value;
		return res;
	}
};

template <typename T>
constexpr Matrix4<T> operator*(const T& value, const Matrix4<T>& matrix) {
	return matrix * value;
}