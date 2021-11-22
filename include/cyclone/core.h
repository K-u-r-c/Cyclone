#include <math.h>

#include "precision.h"

#ifndef CYCLONE_CORE_H
#define CYCLONE_CORE_H

namespace cyclone {

/**
* Holds a vector in three dimensions.
* Four data members are alocated to ensure alignment in memory.
*/
class Vector3 {
public:
	//Value along the x axis.
	real x;

	//Value along the y axis.
	real y;

	//Value along the z axis.
	real z;
private:
	// Padding to ensure four word allignment.
	real pad;

public:
	// Default constructor creates zero vector.
	Vector3() : x(0), y(0), z(0) {}

	// The explicit constructor creates a vector with the given components.
	Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}

	const static Vector3 GRAVITY;
	const static Vector3 HIGH_GRAVITY;
	const static Vector3 UP;
	const static Vector3 RIGHT;
	const static Vector3 OUT_OF_SCREEN;
	const static Vector3 X;
	const static Vector3 Y;
	const static Vector3 Z;
	
	// Multiply this vector by a given scalar.
	void operator*=(const real scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	// Returns a copy of this vector scaled by a given scalar value.
	Vector3 operator*(const real scalar) const {
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	// Add other vector to this vector.
	void operator+=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

	// Returns the value of the given vector added to this vector.
	Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	// Subtract other vector from this vector.
	void operator-=(const Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	// Returns the value of the given vector subtracted from this vector.
	Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	// Adds the given vector to this, scaled by the given scalar value.
	void addScaledVector(const Vector3& v, real scale) {
		x += v.x * scale;
		y += v.y * scale;
		z += v.z * scale;
	}

	// Calculates and returns a component-wise product of this vector with the given vector.
	Vector3 componentProduct(const Vector3& v) const {
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	// Performs a component-wise product of this vector with the given vector and sets this to its result.
	void componentProductUpdate(const Vector3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}

	// Calculates and returns a scalar product of this vector with the given vector.
	real scalarProduct(const Vector3& v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	// Calculates and returns a scalar product of this vector with the given vector.
	real operator*(const Vector3& v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	// Gets the magnitude of this vector.
	real magnitude() const {
		return real_sqrt(x * x + y * y + z * z);
	}

	// Gets the squared magnitude of this vector.
	real squareMagnitude() const {
		return x * x + y * y + z * z;
	}

	// Turns a non-zero vector into a vector of unit length.
	void normalize() {
		real l = magnitude();
		if (l > 0) {
			(*this) *= ((real)1) / l;
		}
	}

	// Calculates and return the vector product of this vector with the given vector.
	Vector3 vectorProduct(const Vector3& v) const {
		return Vector3(y * v.z - z * v.y,
					   z * v.x - x * v.z,
					   x * v.y - y * v.x);
	}

	// Updates this vector to be the vector product of its current value and the given vector.
	void operator%=(const Vector3& v) {
		(*this) = vectorProduct(v);
	}

	// Calculates and return the vector product of this vector with the fiven vector.
	Vector3 operator%(const Vector3& v) const {
		return Vector3(y * v.z - z * v.y,
					   z * v.x - x * v.z,
					   x * v.y - y * v.x);
	}

	// Flips all the components of the vector.
	void invert() {
		x = -x;	y = -y; z = -z;
	}

	// Zero all the components of the vector.
	void clear() { x = y = z = 0; }
};

} // namespace cyclone

#endif // CYCLONE_CORE_H