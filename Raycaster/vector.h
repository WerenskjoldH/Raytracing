#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>
#include <iostream>

namespace rn {
	class vector3f {
	private:

	public:
		float x;
		float y;
		float z;

		// Outside function declerations
		float dot(const vector3f& o, const vector3f& v);

		// Getters/Setters
		float r() const
		{
			return x;
		}

		float g() const
		{
			return y;
		}

		float b() const
		{
			return z;
		}

		// Constructors
		vector3f(float iX = 0, float iY = 0, float iZ = 0) : x(iX), y(iY), z(iZ) {};

		// Deconstructor
		~vector3f() {}

		// Copy Constructor
		vector3f(const vector3f & v) : x(v.x), y(v.y), z(v.z) {};

		// Operator Overloads
		vector3f& operator=(const vector3f & v)
		{
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		void operator+=(const vector3f & v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		void operator-=(const vector3f & v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		void operator*=(const float & s)
		{
			x *= s;
			y *= s;
			z *= s;
		}

		void operator/=(const float & s)
		{
			x = x / s;
			y = y / s;
			z = z / s;
		}

		// This is NOT the dot product
		vector3f operator*(const vector3f & v) const
		{
			return vector3f(x*v.x, y*v.y, z*v.z);
		}

		vector3f operator/(const float s) const
		{
			return vector3f(x / s, y / s, z / s);
		}

		vector3f operator*(const float s) const
		{
			return vector3f(s*x, s*y, x*z);
		}

#ifdef _MATRIX_H_
		vector3f operator*(matrix m) const
		{
			return vector3f(x*m(0, 0) + y * m(1, 0) + z * m(2, 0),
				x*m(0, 1) + y * m(1, 1) + z * m(2, 1),
				x*m(0, 2) + y * m(1, 2) + z * m(2, 2));
		}
#endif

		vector3f operator-(const vector3f & v) const
		{
			return vector3f(x - v.x, y - v.y, z - v.z);
		}

		vector3f operator+(const vector3f & v) const
		{
			return vector3f(x + v.x, y + v.y, z + v.z);
		}

		vector3f operator-() const
		{
			return vector3f(-x, -y, -z);
		}

		float& operator[](int i)
		{
			switch (i)
			{
			case 2:
				return z;
				break;
			case 1:
				return y;
				break;
			case 0:
				return x;
				break;
			default:
				std::cout << "ERROR::VECTOR::OUT OF BOUNDS REQUEST" << std::endl;
			}
		}

		float operator[](int i) const
		{
			switch (i)
			{
			case 2:
				return z;
				break;
			case 1:
				return y;
				break;
			case 0:
				return x;
				break;
			default:
				std::cout << "ERROR::VECTOR::OUT OF BOUNDS REQUEST" << std::endl;
			}
		}

		vector3f cross(const vector3f & v) const
		{
			return vector3f(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x);
		}

		vector3f unit()
		{
			return vector3f(*this / this->magnitude());
		}

		void normalize()
		{
			(*this) = (*this).unit();
		}

		float angleBetweenVector(vector3f & v)
		{
			return std::acos(dot(v, (*this)) / v.magnitude() * this->magnitude());
		}

		float magnitude()
		{
			return std::sqrtf(x * x + y * y + z * z);
		}

		float squaredMagnitude()
		{
			return x * x + y * y + z * z;
		}
	};

	std::ostream& operator<<(std::ostream& os, const vector3f& v)
	{
		return os << v.x << " " << v.y << " " << v.z;
	}

	vector3f operator*(float s, const vector3f& v)
	{
		return vector3f(s*v.x, s*v.y, s*v.z);
	}

	float dot(const vector3f& o, const vector3f& v)
	{
		return o.x * v.x + o.y * v.y + o.z * v.z;
	}

	inline vector3f unitVector(vector3f v)
	{
		return v / v.magnitude();
	}

	inline vector3f reflect(const vector3f v, const vector3f n)
	{
		return v - 2.0f * dot(v, n) * n;
	}

	// Returns a viable direction in a unit sphere
	inline rn::vector3f randomInUnitSphere()
	{
		rn::vector3f p;
		do {
			p = 2.0f * rn::vector3f(rand() / (RAND_MAX + 1.0), rand() / (RAND_MAX + 1.0), rand() / (RAND_MAX + 1.0)) - rn::vector3f(1, 1, 1);
		} while (p.squaredMagnitude() >= 1.0f);
		return p;
	}
}

#endif