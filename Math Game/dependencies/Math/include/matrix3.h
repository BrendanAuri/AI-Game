#pragma once

class Matrix3 {
public:
	union {
		struct {
			float	m11, m12, m13,
					m21, m22, m23,
					m31, m32, m33;
		};
		float point[3];
	};

	Matrix3();
	Matrix3(float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33);

	operator float*();

	Matrix3 operator*(Matrix3 mat);

	void setRotateX(float theta);
	void setRotateY(float theta);
	void setRotateZ(float theta);
};