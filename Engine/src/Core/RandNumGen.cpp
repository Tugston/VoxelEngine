/*
* File: RandNumGen.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-01-15 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "RandNumGen.h"

namespace Engine::Utility
{
	static std::mt19937 gen;

	bool InitializeRandomGenerators()
	{		
		srand(time(NULL));
		std::random_device rd;
		gen = std::mt19937(rd());
		return true;	
	}

	double RandomFloatInRange(const double min, const double max)
	{
		if (min >= max)
		{
			LOG_MSG("<RandNumGen.h> (RandomFloatInRange) Min Must Be Less Than Max!");
			return 0.0;
		}

		std::uniform_real_distribution<> dis(min, max);
		return dis(gen);
	}

	long RandomNumberInRange(const long min, const long max)
	{
		if (min >= max)
		{
			LOG_MSG("<RandNumGen.h> (RandomNumberInRange) Min Must Be Less Than Max!");
			return 0;
		}

		std::uniform_int_distribution<> dis(min, max);
		return dis(gen);
	}
}