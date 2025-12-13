/*
* File: Math.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-12 (yyyy/mm/dd)
*
* Description: The engine's own math implementations to abstract glm from the user application
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
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

		void Floor()
		{
			x = std::floor(x);
			y = std::floor(y);
			z = std::floor(z);
		}

		Vector3<t> Absolute() const
		{
			return Vector3<t>(std::abs(x), std::abs(y), std::abs(z));
		}

		double Length() const
		{
			return std::sqrt((x * x) + (y * y) + (z * z));
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
		Vector3<t> Cross(const Vector3<t>& other) const
		{
			return Vector3<t>{
				(y * other.z) - (z * other.y),
				(z * other.x) - (x * other.z),
				(x * other.y) - (y * other.x)
			};
		}

		//literally the same as above just copy pasted and adjusted
		static Vector3<t> Cross(const Vector3<t>& first, const Vector3<t>& second)
		{
			return Vector3<t>{
				(first.y * second.z) - (first.z * second.y),
				(first.z * second.x) - (first.x * second.z),
				(first.x * second.y) - (first.y * second.x)
			};
		}

		Vector3 Normalize()
		{
			t length = std::sqrt((x * x) + (y * y) + (z * z));
			return Vector3(x / length, y / length, z / length);
		}

		static Vector3 Normalize(const Vector3<t>& vector)
		{
			t length = std::sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z + vector.z));
			if (length > 0)
				return Vector3(vector.x / length, vector.y / length, vector.z / length);
			else
				return Vector3(vector.x, vector.y, vector.z);
		}
	};

	struct Rotator2
	{

	};

	struct Rotator3
	{

	};

}
