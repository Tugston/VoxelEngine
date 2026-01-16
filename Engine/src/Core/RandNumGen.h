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

//ENGN
#include "Logger.h"

//STND
#include <random>

namespace Engine::Utility
{
	/* INTERNAL USE ONLY DO NOT OVERRIDE */
	bool InitializeRandomGenerators();

	double RandomFloatInRange(const double min, const double max);
	long RandomNumberInRange(const long min, const long max);

}


