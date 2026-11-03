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

/**
* @file Math.h
* @brief Viper's own math library implementation which supports only the supported types used by the engine.
* 
* @details This math library is utilized in order to abstract glm from the user application. As of version 0.0.2 it provides Vectors and Rotators in both 2d and 3d with full math utility functions for each. Some utilities are statically copied as well to provide calculations without instantiating a new class object.
* 
* @author Vincent Pierce
* @date December 12, 2025
*/

//STND
#include <utility>
#include <cmath>

namespace Viper::Maths
{
	template<typename t>
	struct Vector2
	{
		/// Assigns the #x and #y values to 0 by default.
		Vector2() = default;
		/// Create a new Vector2 and assign a custom #x and #y value.
		Vector2(t x, t y) : x(x), y(y) {}

		/// Left and right direction
		t x = 0;
		/// Up and down direction
		t y = 0;

		/**
		* @brief Addition operator overload function
		* @details Adds the #x and #y value of the second vector to the first one.
		* 
		* @param[in] other The second vector being added to this one.
		* @return A new Vector2 from the calculated operation.
		*/
		Vector2<t> operator+(const Vector2<t>& other) const { return(Vector2<t>(other.x + x, other.y + y)); }

		/**
		* @brief Subtraction operator overload function
		* @details Subtracts the second #x and #y vlaue from this one.
		* 
		* @param[in] other The second vector being subtracted from this one.
		* @return A new Vector2 from the subtracted operation.
		*/
		Vector2<t> operator-(const Vector2<t>& other) const { return(Vector2<t>(x - other.x, y - other.y)); }

		//need to add multiplying.....

		/**
		* @brief Assignment operator overload function
		* @details Checks to ensure the current Vector2 is not the same object as the reference being passed in. Assign the other #x value to the current one, and do the same for y. Then finally return.
		*
		* @param[in] other The vector that is being assigned to this current one.
		* 
		* @return Dereferenced pointer to the current Vector2. If the other Vector2 parameter is equal to the current one, just return the current as is. 
		*/
		Vector2<t> operator=(const Vector2<t>& other)
		{
			if (this == &other) return *this;
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		//ADD FLOOR AND CEIL FUNCTIONS!

		//ADD ROUNDING WITH THE DECIMAL PLACE!

		//ADD LENGTH!

		/**
		* @brief Caculates the floating scale that represent the two Vector2 direction simularity.
		* @details Multiply this #x by the other #x value. Do the same for #y and add the products together.
		* 
		* @param[in] other The other vector needing to be evaluated for the dot product.
		* @return Calculated dot product.
		*/
		t Dot(const Vector2<t>& other) const
		{
			return (x * other.x) + (y * other.y);
		}

		/**
		* @brief Dot utility for two uninstantiated Vector2 classes.
		* @details Calculates the floating scale that represents the two Vector2 direction simularity.
		* 
		* @param[in] first The first Vector2 of the calculation.
		* @param[in] second The second Vector2 needed for the calculation.
		* @note The order of the first and second Vector2 does not matter.
		* 
		* @return Calculated dot product.
		*/
		static t Dot(const Vector2<t>& first, const Vector2<t>& second)
		{
			return (first.x * second.x) + (first.y * second.y);
		}

		/**
		* @brief Calculates an orthogonal third direction from both vectors utilizing the current one.
		* @details Subtracts the current Vector2 #x from the other's y. Performs the same operation for the other two parameters. Finally subtracts both results. This operation follows the (flat) Left Hand rule.
		* 
		* @return The calculated orthogonal vector.
		*/
		t Cross(const Vector2<t>& other) const
		{
			return (x - other.y) - (y - other.x);
		}

		/**
		* @brief Calculates an orthogonal third direction from two uninstantiated vectors.
		* @details Subtracts the first Vector2 #x from the second Vector2 #y. Perform the same operation for the first Vector #y and second Vector2 #x. Then subtract both results. 
		* 
		* @return The calculated orthogonal vector.
		* @note Order of the parameters matter. Swapping the first and second Vector2 causes a positive and negative cross product differential.
		*/
		static t Cross(const Vector2<t>& first, const Vector2<t>& second)
		{
			return (first.x - second.y) - (first.y - second.x);
		}

		/**
		* @brief Resize the Vector2 down to a scaled direction between 0 and 1 while maintaining relevancy.
		* @details Calculates the total length of the Vector2 by square rooting the results of #x squared added to #y squared. Then the final normalized vector has #x and #y divided by this length value.
		* 
		* @return The normalized value between 0 and 1 that is relevant to the original value.
		* 
		* @warning As of version 0.0.2, this function will have a serious problem if you hit the max size of t, ie (t_max * t_max). This issue is technically present for all the functions in the Vector2. As of the current version, the solution is to not intentionally cause undefined behavior by Signed Overflow.
		*/
		Vector2 Normalize() //need to check if the length is zero! Also, use the Length() function.
		{
			t length = std::sqrt((x * x) + (y * y));
			return Vector2(x / length, y / length);
		}

	};

	template<typename t>
	struct Vector3
	{
		/// Assign the #x, #y, and #z values to 0 by default.
		Vector3() = default;
		/// Create a new Vector3 and assign a custom #x, #y, and #z value.
		Vector3(t x, t y, t z) : x(x), y(y), z(z) {}
		/// Create a Vector3 from a Vector2 and assign the #z value to 0.
		Vector3(const Vector2<t>& vec2) : x(vec2.x), y(vec2.y) {}

		/// Left and right direction.
		t x = 0;
		/// Up and down direction.
		t y = 0;
		/// Forward and backwards direction, or depth.
		t z = 0;
		
		/**
		* @brief Addition operator overload function.
		* @details Adds the current Vector3 to the provided one.
		* 
		* @param[in] other The Vector3 to be sumed together.
		* @return A new Vector3 sum of both vectors.
		*/
		Vector3<t> operator+(const Vector3<t>& other) const { return Vector3<t>(x + other.x, y + other.y, z + other.z); }

		/**
		* @brief Subtraction operator overload function.
		* @details Subtracts the provided Vector3 parameter from the current one.
		*
		* @param[in] other The Vector3 to be used as the subtrhend (the second value).
		* @return A new Vector3 representing the difference.
		*/
		Vector3<t> operator-(const Vector3<t>& other) const { return Vector3<t>(x - other.x, y - other.y, z - other.z); }

		/**
		* @brief Multiplication operator overload function for Vector3.
		* @details Calculates the product by multiplying the #x the #y and the #z from the current Vector3 to the provided Vector3 parameter.
		* 
		* @param[in] other The Vector3 to be mutliplied to the current Vector3.
		* @return A new Vector3 representing the product.
		*/
		Vector3<t> operator*(const Vector3<t>& other) const { return Vector3<t>(x * other.x, y * other.y, z * other.z); }

		/**
		* @brief Multiplication operator overload function for a float.
		* @details Calculates the product by multiplying the #x the #y and the #z from this Vector3 to the scalar parameter
		* 
		* @param[in] scalar Float to multiply to each Vector3 value
		* @return A new Vector3 representing the product.
		*/
		Vector3<t> operator*(float scalar) const { return Vector3<t>(x * scalar, y * scalar, z * scalar); }

		/**
		* @brief Assignment operator overload function
		* @details Check to ensure the assigned Vector3 is not the same as the current one. If it is, just return the current back. Then, assign the #x, #y, and #z values of the current Vector3 to equal the second one on the right hand side of the sign.
		* 
		* @param[in] other The Vector3 to be assigned to the one on the left side of the operation sign.
		* @return Reference of the current Vector3 to allow chaining.
		*/
		Vector3<t> operator=(const Vector3<t>& other)
		{
			if (this == &other) return *this;
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
			return *this;
		}


		///Round all three values down to the next whole number.
		void Floor()
		{
			x = std::floor(x);
			y = std::floor(y);
			z = std::floor(z);
		}

		//add ceil

		//add rounding with the decimal place

		/**
		* @brief Determine the numerical distance of each value regardless of direction.
		* @details Call the std::abs() function for #x, #y, and #z to convert negative values to positive.
		* @return A new Vector3 with only positive values
		*/
		Vector3<t> Absolute() const
		{
			return Vector3<t>(std::abs(x), std::abs(y), std::abs(z));
		}

		/**
		* @brief Calculates the straight line distance from the world origin to this Vector3.
		* @details Squares each value with itself, adds them all together, and finally calculate the square root.
		* @return The double variable value of the distance from the world's origin.  
		*/
		double Length() const
		{
			return std::sqrt((x * x) + (y * y) + (z * z));
		}

		/**
		* @brief Caculates the floating scale that represent the two Vector2 direction simularity.
		* @details Multiplies this Vector3 #x by the other Vector3 #x. Do the same for #y and #z as well. Then add all the sums together.
		*
		* @param[in] other The other vector to have directions compared to.
		* @return The calculated dot product.
		*/
		t Dot(const Vector3<t>& other)
		{
			return (x * other.x) + (y * other.y) + (z * other.z);
		}

		/**
		* @brief Calculates the floating scale that represents the two Vector2 direction's simularity.
		* @details Multiplies this Vector3 #x by the other Vector3 #x. Do the same for #y and #z as well. Then add all the sums together. Static alternative for the Dot() to be able to calculate the Dot product without instantiating a Vector3.
		* 
		* @param[in] first The first Vector3 needing to be compared.
		* @param[in] second The second Vector3 needing to be compared.
		* @note The ordering of the first and second Vector3 does not matter.
		* 
		* @return The calculated dot product.
		*/
		static t Dot(const Vector3<t>& first, const Vector3<t>& second)
		{
			return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
		}

		/**
		* @brief Calculates an orthogonal third direction from the current Vector3 and provided other one.
		* @details Subtracts the prodcut of this Vector3's z and the other Vector3's #y from the product of this Vector3's #y and the other Vector3's #z. Utilizes this value as the new #x value. Then subtracts the product of this #x and other's #z from the product of this #z and other's #x for the new #y value. Finally subtract the prodcut of this #y and other's #x from the product of this #x and other #y. Utilize this as the new Z value. Utilizes the left hand rule for the calculation.
		* 
		* ## Visualization of Operation
		* @code
		* return Vector3<t>{
		*	(y * other.z) - (z * other.y),
		*	(z * other.x) - (x * other.z),
		*	(x * other.y) - (y * other.x)
		* }
		* @endcode
		* 
		* @param[in] other The other Vector3 to be used to find the third orthoganal Vector3.
		*
		* @return The calculated orthogonal vector.
		*/
		Vector3<t> Cross(const Vector3<t>& other) const
		{
			return Vector3<t>{
				(y * other.z) - (z * other.y),
				(z * other.x) - (x * other.z),
				(x * other.y) - (y * other.x)
			};
		}

		/**
		* @brief Calculates an orthogonal third direction based on the two provided Vector3 parameters.
		* @details Subtracts the prodcut of this Vector3's z and the other Vector3's #y from the product of this Vector3's #y and the other Vector3's #z. Utilizes this value as the new #x value. Then subtracts the product of this #x and other's #z from the product of this #z and other's #x for the new #y value. Finally subtract the prodcut of this #y and other's #x from the product of this #x and other #y. Utilize this as the new Z value. Utilizes the left hand rule for the calculation. Static function to allow the calculation to be done with uninstantiated Vector3's.
		* 
		* ## Visualization of Operation
		* @code
		* return Vector3<t>{
		*	(y * other.z) - (z * other.y),
		*	(z * other.x) - (x * other.z),
		*	(x * other.y) - (y * other.x)
		* }
		* @endcode
		* 
		* @param[in] first The 'thumb' Vector3 needed for the cross calculation.
		* @param[in] second The 'pointer finger' Vector3 needed for the cross calculation.
		* @note Order of the parameters matter. Swapping the first and second Vector2 causes a positive and negative cross product differential.
		* 
		* @return The orthogonal third Vector3.
		*/
		static Vector3<t> Cross(const Vector3<t>& first, const Vector3<t>& second)
		{
			return Vector3<t>{
				(first.y * second.z) - (first.z * second.y),
				(first.z * second.x) - (first.x * second.z),
				(first.x * second.y) - (first.y * second.x)
			};
		}

		/**
		* @brief Resize the Vector2 down to a scaled direction between 0 and 1 while maintaining relevancy.
		* @details Calls Length() to get the total length of this Vector3 from the world origin. Then the final normalized vector has #x, #y, and #z divided by the calculated length value.
		*
		* @return The normalized value between 0 and 1 that is relevant to the original value.
		*
		* @warning As of version 0.0.2, this function will have a serious problem if you hit the max size of t, ie (t_max * t_max). This issue is technically present for all the functions in the Vector2. As of the current version, the solution is to not intentionally cause undefined behavior by Signed Overflow.
		*/
		Vector3 Normalize()
		{
			//fix this to check if zero
			t lengthStore = Length();
			return Vector3(x / lengthStore, y / lengthStore, z / lengthStore);
		}

		/**
		* @brief Resize the Vector2 down to a scaled direction between 0 and 1 while maintaining relevancy.
		* @details Calls Length() to get the total length of this Vector3 from the world origin. Then the final normalized vector has #x, #y, and #z divided by the calculated length value. Static version to allow normalization of uninitialized Vector3 values.
		*
		* @return The normalized value between 0 and 1 that is relevant to the original value.
		*
		* @warning As of version 0.0.2, this function will have a serious problem if you hit the max size of t, ie (t_max * t_max). This issue is technically present for all the functions in the Vector2. As of the current version, the solution is to not intentionally cause undefined behavior by Signed Overflow.
		*/
		static Vector3 Normalize(const Vector3<t>& vector)
		{
			//use the length function instead of redoing this!
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
