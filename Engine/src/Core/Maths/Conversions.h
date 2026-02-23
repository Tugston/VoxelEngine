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

//ENGN
#include "Math.h"

namespace Engine::Maths
{
	unsigned int RGBtoHex(const Vector3<uint8_t>& color);
}

