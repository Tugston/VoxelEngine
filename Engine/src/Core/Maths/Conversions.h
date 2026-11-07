/*
* File: Conversions.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-01-27 (yyyy/mm/dd)
*
* Description: Math and logic conversions useful throughout all user applications
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

/**
* @file Conversions.h
* @brief Helpful functions for converting unit measurements and other conversions
* 
* @details These functions are mostly utilized internally and by the editor, but exposed in the public engine. As of version 0.0.2 there are not very many conversions (1 total) and this file will be update with more details then.
* 
* @author Vincent Pierce
* @date January 27, 2026
*/

//ENGN
#include "Math.h"

namespace Viper::Maths
{
	/**
	* @brief Convert a general rgb color to a Hexadecimal representation of the same color.
	* @details Converts the Vector3 holding rgb values to hexadecimal by bit shifting the x (red) over 2 bytes, the y (green) over 1 byte, and the z (blue) over by a single byte.
	* 
	* @param[in] color The rgb color needing to be converted.
	* 
	* @return A compacted hexadecimal color inside an integer.
	*/
	unsigned int RGBtoHex(const Vector3<uint8_t>& color);
}

