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

		float operator*(const vector3f & v) const
		{
			return x * v.x + y * v.y + z * v.z;
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
			return std::acos(v * (*this) / v.magnitude() * this->magnitude());
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

	inline vector3f unitVector(vector3f v)
	{
		return v / v.magnitude();
	}

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
		return o * v;
	}

	class vector4f {
	private:

	public:
		float x;
		float y;
		float z;
		float w;

		// Constructors
		vector4f() : x(0.f), y(0.f), z(0.f), w(1.f) {};
		vector4f(float iX = 0, float iY = 0, float iZ = 0, float iW = 1) : x(iX), y(iY), z(iZ), w(iW) {};

		// Deconstructor
		~vector4f() {}

		// Copy Constructor
		vector4f(const vector4f & v) : x(v.x), y(v.y), z(v.z), w(v.w) {};

		// Operator Overloads
		vector4f& operator=(const vector4f & v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;

			return *this;
		}

		void operator+=(const vector4f & v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}

		void operator-=(const vector4f & v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
		}

		void operator*=(const float & s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
		}

		void operator/=(const float & s)
		{
			x = x / s;
			y = y / s;
			z = z / s;
			w = w / s;
		}

		float operator*(const vector4f & v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		vector4f operator/(const float s) const
		{
			return vector4f(x / s, y / s, z / s, w / s);
		}

		vector4f operator*(const float s) const
		{
			return vector4f(s*x, s*y, x*z, w*z);
		}

#ifdef _MATRIX_H_
		vector4f operator*(matrix m) const
		{
			return vector4f(x*m(0, 0) + y * m(1, 0) + z * m(2, 0) + w * m(3, 0),
				x*m(0, 1) + y * m(1, 1) + z * m(2, 1) + w * m(3, 1),
				x*m(0, 2) + y * m(1, 2) + z * m(2, 2) + w * m(3, 2),
				x*m(0, 3) + y * m(1, 3) + z * m(2, 3) + w * m(3, 3));
		}
#endif

		vector4f operator-(const vector4f & v) const
		{
			return vector4f(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		vector4f operator+(const vector4f & v) const
		{
			return vector4f(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		vector3f operator-() const
		{
			return vector3f(-x, -y, -z);
		}

		float& operator[](int i)
		{
			switch (i)
			{
			case 3:
				return w;
				break;
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
			case 3:
				return w;
				break;
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

		vector4f unit()
		{
			return vector4f(*this / this->magnitude());
		}

		void normalize()
		{
			(*this) = (*this).unit();
		}

		float angleBetweenVector(vector4f & v)
		{
			return std::acos(v * (*this) / v.magnitude() * this->magnitude());
		}

		float magnitude()
		{
			return std::sqrtf(x*x + y * y + z * z + w * w);
		}
		float squaredMagnitude()
		{
			return x*x + y * y + z * z + w * w;
		}
};

	std::ostream& operator<<(std::ostream& os, const vector4f& v)
	{
		return os << v.x << " " << v.y << " " << v.z << " " << v.w;
	}

	vector4f operator*(float s, const vector4f& v)
	{
		return vector4f(s*v.x, s*v.y, s*v.z, s*v.w);
	}

}

#endif