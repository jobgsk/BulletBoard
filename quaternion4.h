#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <cmath>


template <class T>
/**
* Holds a three degree of freedom orientation.
*
* Quaternions have
* several mathematical properties that make them useful for
* representing orientations, but require four items of data to
* hold the three degrees of freedom. These four items of data can
* be viewed as the coefficients of a complex number with three
* imaginary parts. The mathematics of the quaternion is then
* defined and is roughly correspondent to the math of 3D
* rotations. A quaternion is only a valid rotation if it is
* normalised: i.e. it has a length of 1.
*
* @note Angular velocity and acceleration can be correctly
* represented as vectors. Quaternions are only needed for
* orientation.
*/
class Quaternion4
{
public:
	union {
		struct {
			/**
			* Holds the real component of the quaternion.
			*/
			T w;

			/**
			* Holds the first complex component of the
			* quaternion.
			*/
			T x;

			/**
			* Holds the second complex component of the
			* quaternion.
			*/
			T y;

			/**
			* Holds the third complex component of the
			* quaternion.
			*/
			T z;
		};

		/**
		* Holds the quaternion data in array form.
		*/
		T data[4];
	};

	// ... other Quaternion code as before ...

	/**
	* The default constructor creates a quaternion representing
	* a zero rotation.
	*/
	Quaternion4() : w(1), x(0), y(0), z(0) {}

	/**
	* The explicit constructor creates a quaternion with the given
	* components.
	*
	* @param w The real component of the rigid body's orientation
	* quaternion.
	*
	* @param x The first complex component of the rigid body's
	* orientation quaternion.
	*
	* @param y The second complex component of the rigid body's
	* orientation quaternion.
	*
	* @param z The third complex component of the rigid body's
	* orientation quaternion.
	*
	* @note The given orientation does not need to be normalised,
	* and can be zero. This function will not alter the given
	* values, or normalise the quaternion. To normalise the
	* quaternion (and make a zero quaternion a legal rotation),
	* use the normalise function.
	*
	* @see normalise
	*/
	Quaternion4(const T w, const T x, const T y, const T z)
		: w(w), x(x), y(y), z(z)
	{
	}

	/**
	* Normalises the quaternion to unit length, making it a valid
	* orientation quaternion.
	*/
	void normalise()
	{
		T d = w*w + x*x + y*y + z*z;

		// Check for zero length quaternion, and use the no-rotation
		// quaternion in that case.
		if (d < real_epsilon) {
			r = 1;
			return;
		}

		d = ((T)1.0) / sqrt(d);
		w *= d;
		x *= d;
		y *= d;
		z *= d;
	}

	/**
	* Multiplies the quaternion by the given quaternion.
	*
	* @param multiplier The quaternion by which to multiply.
	*/
	void operator *=(const Quaternion4 &multiplier)
	{
		Quaternion4 q = *this;
		w = q.w*multiplier.w - q.x*multiplier.x -
			q.y*multiplier.y - q.z*multiplier.z;
		x = q.w*multiplier.x + q.x*multiplier.w +
			q.y*multiplier.z - q.z*multiplier.y;
		y = q.w*multiplier.y + q.y*multiplier.w +
			q.z*multiplier.x - q.x*multiplier.z;
		z = q.w*multiplier.z + q.z*multiplier.w +
			q.x*multiplier.y - q.y*multiplier.x;
	}

	/**
	* Adds the given vector to this, scaled by the given amount.
	* This is used to update the orientation quaternion by a rotation
	* and time.
	*
	* @param vector The vector to add.
	*
	* @param scale The amount of the vector to add.
	*/
	void addScaledVector(const Vector3<float>& vector, T scale)
	{
		Quaternion4 q(0,
			vector.x * scale,
			vector.y * scale,
			vector.z * scale);
		q *= *this;
		w += q.w * ((T)0.5);
		x += q.x * ((T)0.5);
		y += q.y * ((T)0.5);
		z += q.z * ((T)0.5);
	}

	void rotateByVector(const Vector3<float>& vector)
	{
		Quaternion4 q(0, vector.x, vector.y, vector.z);
		(*this) *= q;
	}
};

#endif /* QUATERNION_H_ */