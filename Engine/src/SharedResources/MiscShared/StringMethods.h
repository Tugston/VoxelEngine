/*
* File: StringMethods.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-01-28 (yyyy/mm/dd)
*
* Description: optimized string functions to do stnd operations without error checking
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

namespace Engine::Utility
{
	//remove atoi error checking
	inline int FastATOI(const char* string)
	{
		int val = 0;
		while (*string)
		{
			val = val * 10 + (*string++ - '0');
		}
		return val;
	}
}
