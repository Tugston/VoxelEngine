/*
* File: RandNumGen.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-01-15 (yyyy/mm/dd)
*
* Description: Utility functions for generating random numbers
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

/**
* @file RandNumGen.h
* @brief Utility functions for generating various random values
* 
* @details Available functions for Generating random floats, random integers, and random characters in range. These functions also provide a scaled variant that allow a value from 0 - 1 for example. Also have functions for random characters, booleans, and these have scaled alternative functions as well.
* 
* @author Vincent Pierce
* @date January 15, 2026
*/

//ENGN
#include "Logger.h"

//STND
#include <random>

namespace Viper::Utility
{
	/* INTERNAL USE ONLY DO NOT OVERRIDE */
	/**
	* @brief Initializes the random number generators used by the application.
	* @details Seeds the standard library random number generator using the current system time and initializes the Mersenne Twister engine using a seed obtained from std::random_device.
	* 
	* @return True upon completion
	* @warning This is for internal engine use setup only! Please do not override or call in any derived applications. The function is exposed to do so, but it will reset the generators and cause unpredictable behaviour.
	*/
	bool InitializeRandomGenerators();

	/**
	* @brief Generates a uniformly distributed random floating value within specified range.
	* @pre The InitializeRandomGenerators() function must be called before executing this function.
	* 
	* @param[in] min The inclusive lower bound of the random range.
	* @param[in] max The inclusive upper bound of the random range.
	* 
	* @return A randomly generated floating value within the specified range.
	* @note Returns 0 if min is greater than the max.
	*/
	double RandomFloatInRange(const double min, const double max);

	/**
	* @brief Generate a uniformly distributed random integer value within the specified range.
	* @pre The InitializeRandomGenerators() function must be called before executing this function.
	* 
	* @param[in] min The inclusing lower bound of the random range.
	* @param[in] max The inclusing upper bound of the random range.
	* 
	* @return A randomly generated integral value within the specified range.
	* @note Returns 0 if the min is greater than the max.
	*/
	long RandomNumberInRange(const long min, const long max);

}


