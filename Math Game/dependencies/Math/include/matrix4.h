#pragma once

class Matrix4 {
public:
	union {
		struct {
			float	m11, m12, m13, m14,
					m21, m22, m23, m24,
					m31, m32, m33, m34,
					m41, m42, m43, m44;
		};
		float point[4];
	};

	Matrix4();
	Matrix4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44);

	operator float*();

	Matrix4 operator*(Matrix4 mat);

	void setRotateX(float theta);
	void setRotateY(float theta);
	void setRotateZ(float theta);
};
