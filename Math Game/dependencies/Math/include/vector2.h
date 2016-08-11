#pragma once
#include <math.h>
#include "matrix2.h"

class Vector2
{
public:
	union {
		struct {
			float x, y;
		};
		float point[2];
	};
	Vector2();
	Vector2(float x, float y);
	Vector2 operator*(Vector2 vec);
	Vector2 operator/(Vector2 vec);
	Vector2 operator+(Vector2 vec);
	Vector2 operator-(Vector2 vec);
	Vector2 operator*(float value);
	friend Vector2 operator*(float p_scale, Vector2 vec);
	friend Vector2 operator*(Matrix2 mat, Vector2 vec);

	operator float*();

	float dot(Vector2 vec) { return x * vec.x + y * vec.y; };

	float magnitude() { return sqrtf(x*x + y*y); };
	void normalise() { float mag = magnitude(); x /= mag; y /= mag; };
};