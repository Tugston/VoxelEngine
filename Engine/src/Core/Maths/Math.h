#pragma once
#include <utility>
#include <cmath>

namespace Engine::Maths
{
	template<typename t>
	struct Vector2
	{
		Vector2() = default;
		Vector2(t x, t y) : x(x), y(y) {}
		Vector2(const Vector3<t>& vec3) : x(vec3.x), y(vec3.y) {}

		t x = 0;
		t y = 0;

		Vector2<t> operator+(const Vector2<t>& other) const { return(Vector2<t>(other.x + x, other.y + y)); }
		Vector2<t> operator-(const Vector2<t>& other) const { return(Vector2<t>(x - other.x, y - other.y)); }
		Vector2<t> operator=(const Vector2<t>& other)
		{
			if (this == &other) return;
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

		t Cross(const Vector2<t>& second) const
		{
			return (x - other.y) - (y - other.y);
		}

		static t Cross(const Vector2<t>& first, const Vector2<t>& second)
		{
			return (first.x - second.y) - (first.y - second.y);
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
			if (this == other) return;
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
			const std::pair<Vector2<t>, Vector2<t>> xOut{std::make_pair<Vector2<t>(y, z), Vector2<t>(other.y, other.z)>}; //x determinant
			const std::pair<Vector2<t>, Vector2<t>> yOut{std::make_pair<Vector2<t>(x, z), Vector2<t>(other.x, other.z)>}; //y determinant
			const std::pair<Vector2<t>, Vector2<t>> zOut{std::make_pair<Vector2<t>(x, y), Vector2<t>(other.x, other.y)>}; //z determinant

			const t xProduct = (xOut.first.x * xOut.second.y) - (xOut.first.y * xOut.second.x);
			const t yProduct = (yOut.first.x * yOut.second.y) - (yOut.first.y * yOut.second.x);
			const t zProduct = (zOut.first.x * zOut.second.y) - (zOut.first.y * zOut.second.x);

			return xProduct - yProduct + zProduct;
		}

		//literally the same as above just copy pasted and adjusted
		static t Cross(const Vector3<t>& first, const Vector3<t>& second)
		{
			const std::pair<Vector2<t>, Vector2<t>> xOut{std::make_pair<Vector2<t>(first.y, first.z), Vector2<t>(second.y, second.z)};
			const std::pair<Vector2<t>, Vector2<t>> yOut{std::make_pair<Vector2<t>(first.x, first.z), Vector2<t>(second.x, second.z)};
			const std::pair<Vector2<t>, Vector2<t>> zOut{std::make_pair<Vector2<t>(first.x, first.y), Vector2<t>(second.x, second.y)};

			const t xProduct = (xOut.first.x * xOut.second.y) - (xOut.first.y * xOut.second.x);
			const t yProduct = (yOut.first.x * yOut.second.y) - (yOut.first.y * yOut.second.x);
			const t zProduct = (zOut.first.x * zOut.second.y) - (zOut.first.y * zOut.second.x);

			return xProduct - yProduct + zProduct;
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
