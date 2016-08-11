#pragma once
#include <math.h>
#include "matrix3.h"

class Vector3
{
public:
	union {
		struct {
			float x, y, z;
		};
		float point[3];
	};
	Vector3();
	Vector3(float x, float y, float z);
	Vector3 operator*(Vector3 vec);
	Vector3 operator/(Vector3 vec);
	Vector3 operator+(Vector3 vec);
	Vector3 operator-(Vector3 vec);
	Vector3 operator*(float value);
	friend Vector3 operator*(float p_scale, Vector3 vec);
	friend Vector3 operator*(Matrix3 mat, Vector3 vec);

	operator float*();

	float dot(Vector3 vec) { return x * vec.x + y * vec.y + z * vec.z; }

	Vector3 cross(Vector3 vec) { return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x); }

	float magnitude() { return sqrtf(this->x*this->x + this->y*this->y + this->z*this->z); }
	void normalise() { 
		float mag = this->magnitude(); 
		this->x /= mag;
		this->y /= mag;
		this->z /= mag; 
	}
};