/*
* File: CameraSettings.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-28 (yyyy/mm/dd)
*
* Description: Basic camera settings that are passed around. ECS could utilize this as well (not currently at that point as of 12/6/2025)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//VENDOR
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Engine::Camera
{
	struct CameraSettings
	{
		//general settings
		float speed = 1.f;
		float sensitivity = .025f;
		UINT8 fov = 40; //removes float precision, but whole numbers are nice regardless

		//view distance
		const float nearPlane = .01f;
		const float farPlane = 1000.f;

		//window settings
		float apectRatio = 0; //CALCULATED IN CAMERA CONSTRUCTORS

		CameraSettings() : speed(3.f), sensitivity(.8f), fov(40.f), nearPlane(.01f), farPlane(10000.f) {};
		CameraSettings(float sensitivity, float speed) : sensitivity(sensitivity), speed(speed) {};
		CameraSettings(float sensitivity, float fov, float speed) : sensitivity(sensitivity), fov(fov), speed(speed) {};
		CameraSettings(float fov) : fov(fov) {};
		CameraSettings(const CameraSettings& settings) = default; //no pointers, so this is fine
	};
}
