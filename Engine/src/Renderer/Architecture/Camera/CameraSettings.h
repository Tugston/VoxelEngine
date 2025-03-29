#pragma once

//VENDOR
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

//this is just a helper struct for the camera's
//this does not have any association with the ecs, although some values may be shared

namespace Engine::Renderer::Settings
{
	struct CameraSettings
	{
		//general settings
		float speed = 2.f;
		float sensitivity = 2.f;
		float fov = 90.f;

		//view distance
		const float nearPlane = .01f;
		const float farPlane = 1000.f;

		//window settings
		float apectRatio = 0; //CALCULATED IN CAMERA CONSTRUCTORS

		CameraSettings() {};
		CameraSettings(float sensitivity, float fov, float speed) : sensitivity(sensitivity), fov(fov), speed(speed) {};
		CameraSettings(float fov) : fov(fov) {};
		CameraSettings(const CameraSettings& settings) = default; //no pointers, so this is fine
	};
}
