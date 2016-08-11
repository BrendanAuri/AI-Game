#pragma once

class Matrix2 {
public:
	union {
		struct {
			float	m11, m12,
					m21, m22;
		};
		float point[2];
	};
	
	Matrix2();
	Matrix2(float m11, float m12,
			float m21, float m22);

	operator float*();

	Matrix2 operator*(Matrix2 mat);

	void setRotateZ(float theta);
};