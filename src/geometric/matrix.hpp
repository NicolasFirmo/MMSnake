#pragma once

template<typename T>
struct Matrix4 {
	struct Row {
		T c[4];
	};

	Row r[4];

	[[nodiscard]] static constexpr Matrix4 identity() {
		return {{
			{{1, 0, 0, 0}},
			{{0, 1, 0, 0}},
			{{0, 0, 1, 0}},
			{{0, 0, 0, 1}},
		}};
	}

	[[nodiscard]] static constexpr Matrix4 orthographic(const T& left, const T& right,
														const T& bottom, const T& up) {
		constexpr T front = -1;
		constexpr T rear  = 1;

		const T midX = (left + right) / 2;
		const T midY = (bottom + up) / 2;
		const T midZ = (-rear + -front) / 2;

		const T scaleX = 2 / (right - left);
		const T scaleY = 2 / (up - bottom);
		const T scaleZ = 2 / (rear - front);

		return {{
			{{scaleX, 0, 0, -midX * scaleX}},
			{{0, scaleY, 0, -midY * scaleY}},
			{{0, 0, scaleZ, -midZ * scaleZ}},
			{{0, 0, 0, 1}},
		}};
	}

	[[nodiscard]] constexpr const T* data() const { return &r[0].c[0]; }

	[[nodiscard]] constexpr Matrix4 operator+(const Matrix4& other) const {
		Matrix4 res;
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
				res.r[i].c[j] = r[i].c[j] + other.r[i].c[j];

		return res;
	}

	[[nodiscard]] constexpr Matrix4 operator-(const Matrix4& other) const {
		Matrix4 res;
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
				res.r[i].c[j] = r[i].c[j] - other.r[i].c[j];

		return res;
	}

	[[nodiscard]] constexpr Matrix4 operator*(const T& value) const {
		Matrix4 res;
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
				res.r[i].c[j] = r[i].c[j] * value;

		return res;
	}
};

template<typename T>
constexpr Matrix4<T> operator*(const T& value, const Matrix4<T>& matrix) {
	return matrix * value;
}
