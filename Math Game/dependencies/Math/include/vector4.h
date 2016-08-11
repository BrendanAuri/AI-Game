#pragma once
#include <math.h>
#include "matrix4.h"

class Vector4
{
public:
	union {
		struct {
			float x, y, z, w;
		};
		float point[4];
	};
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4 operator*(Vector4 vec);
	Vector4 operator/(Vector4 vec);
	Vector4 operator+(Vector4 vec);
	Vector4 operator-(Vector4 vec);
	Vector4 operator*(float value);
	friend Vector4 operator*(float p_scale, Vector4 vec);
	friend Vector4 operator*(Matrix4 mat, Vector4 vec);

	operator float*();

	float dot(Vector4 vec) { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; };

	Vector4 cross(Vector4 vec) { return Vector4(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x, 0); };

	float magnitude() { return sqrtf(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w); };
	void normalise() { 
		float mag = this->magnitude();
		this->x /= mag;
		this->y /= mag;
		this->z /= mag;
		this->w /= mag;
	};
};