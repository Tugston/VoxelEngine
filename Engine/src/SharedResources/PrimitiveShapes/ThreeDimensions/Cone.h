/*
* File: Cone.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-12 (yyyy/mm/dd)
*
* Description: helper function to create a cone mesh as an engine base primitive
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "SharedResources/GenericResources/Mesh.h"

namespace Engine::Utility
{
	Mesh CreateCone(UINT16 sideCount = 8);
}

