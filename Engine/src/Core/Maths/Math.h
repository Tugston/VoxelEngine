#pragma once

//STND
#include <utility>
#include <cmath>

namespace Engine::Maths
{
	template<typename t>
	struct Vector2
	{
		Vector2() = default;
		Vector2(t x, t y) : x(x), y(y) {}

		t x = 0;
		t y = 0;

		Vector2<t> operator+(const Vector2<t>& other) const { return(Vector2<t>(other.x + x, other.y + y)); }
		Vector2<t> operator-(const Vector2<t>& other) const { return(Vector2<t>(x - other.x, y - other.y)); }
		Vector2<t> operator=(const Vector2<t>& other)
		{
			if (this == &other) return *this;
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		t Dot(const Vector2<t>& other) const
		{
			return (x * other.x) + (y * other.y);
		}

		static t Dot(const Vector2<t>& first, const Vector2<t>& second)
		{
			return (first.x * second.x) + (first.y * second.y);
		}

		t Cross(const Vector2<t>& other) const
		{
			return (x - other.y) - (y - other.x);
		}

		static t Cross(const Vector2<t>& first, const Vector2<t>& second)
		{
			return (first.x - second.y) - (first.y - second.x);
		}

		//this will have a serious problem if you hit the max size of t, ie (t_max * t_max)
		//but thats a problem for later, for now the engine is just going to be used very carefully to avoid that
		//this is actually true for all these functions and the ones in the Vector3, and Rotator as well.
		Vector2 Normalize()
		{
			t length = std::sqrt((x * x) + (y * y));
			return Vector2(x / length, y / length);
		}

	};

	template<typename t>
	struct Vector3
	{
		Vector3() = default;
		Vector3(t x, t y, t z) : x(x), y(y), z(z) {}
		Vector3(const Vector2<t>& vec2) : x(vec2.x), y(vec2.y), z(0) {}

		t x = 0;
		t y = 0;
		t z = 0;

		Vector3<t> operator+(const Vector3<t>& other) const { return Vector3<t>(x + other.x, y + other.y, z + other.z); }
		Vector3<t> operator-(const Vector3<t>& other) const { return Vector3<t>(x - other.x, y - other.y, z - other.z); }
		Vector3<t> operator=(const Vector3<t>& other)
		{
			if (this == &other) return *this;
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
			return *this;
		}

		t Dot(const Vector3<t>& other)
		{
			return (x * other.x) + (y * other.y) + (z * other.z);
		}

		static t Dot(const Vector3<t>& first, const Vector3<t>& second)
		{
			return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
		}

		//other value is the direction of cross (left hand rule)
		t Cross(const Vector3<t>& other)
		{
			const t x = (this->y * other.z) - (this->z * other.y);
			const t y = (this->z * other.x) - (this->x * other.z);
			const t z = (this->x * other.y) - (this->y * other.x);

			return x - y + z;
		}

		//literally the same as above just copy pasted and adjusted
		static t Cross(const Vector3<t>& first, const Vector3<t>& second)
		{
			const t x = (first.y * second.z) - (first.z * second.y);
			const t y = (first.z * second.x) - (first.x * second.z);
			const t z = (first.x * second.y) - (first.y * second.x);

			return x - y + z;
		}

		Vector3 Normalize()
		{
			t length = std::sqrt((x * x) + (y * y) + (z * z));
			return Vector3(x / length, y / length, z / length);
		}
	};

	struct Rotator2
	{

	};

	struct Rotator3
	{

	};
}
