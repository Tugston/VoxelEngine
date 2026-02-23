/*
* File: Conversions.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-01-27 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Conversions.h"

namespace Engine::Maths
{
    unsigned int RGBtoHex(const Vector3<uint8_t>& color)
    {
        return (color.z << 16) | (color.y << 8) | (color.x);
    }
}

