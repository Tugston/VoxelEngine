/*
* File: OrthographicCamera.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-28 (yyyy/mm/dd)
*
* Description: Moveable engine camera for orthographic viewpoint views
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

#include "EditorCamera.h"

//WIP - not important right now

namespace Engine::Camera
{
	class OrthographicCamera : public EditorCamera {
	public:
		OrthographicCamera();
		~OrthographicCamera();
	};
}
