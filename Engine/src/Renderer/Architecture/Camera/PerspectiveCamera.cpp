#include "egpch.h"
#include "PerspectiveCamera.h"

//ENGINE
#include "Core/Application.h"

#define CAMERA_SETUP(x, y, z)\
 UpdateProjection(y, z);\
 UpdateRotation(x);\
 UpdateVectors();\

#define WINDOW_WIDTH Application::GetWindow()->GetWidth()
#define WINDOW_HEIGHT Application::GetWindow()->GetHeight()

namespace Engine::Renderer
{
	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, const glm::vec3& rotation, float fov, float speed) :
		m_Settings(2.f, fov, speed), m_Location(position)
	{
		CAMERA_SETUP(rotation, WINDOW_WIDTH, WINDOW_HEIGHT)
	}

	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, float fov) :
		m_Settings(fov), m_Location(position)
	{
		CAMERA_SETUP(glm::vec3(0, 0.f, 90.f), WINDOW_WIDTH, WINDOW_HEIGHT)
	}

	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position) :
		m_Settings(), m_Location(position)
	{
		CAMERA_SETUP(glm::vec3(0.f, 0.f, -90.f), WINDOW_WIDTH, WINDOW_HEIGHT)
	}

	void PerspectiveCamera::ProcessLocation(MoveDirection direction, float deltaTime)
	{
		float velocity = m_Settings.speed * deltaTime;

		m_Location += m_ForwardVector * ((((unsigned int)direction & (unsigned int)MoveDirection::Forward) ? m_Settings.speed : 0.f) * velocity); //forward
		m_Location -= m_ForwardVector * ((((unsigned int)direction & (unsigned int)MoveDirection::Backwards) ? m_Settings.speed : 0.f) * velocity); //backwards
		m_Location += m_RightVector * ((((unsigned int)direction & (unsigned int)MoveDirection::Right) ? m_Settings.speed : 0.f) * velocity); //right
		m_Location -= m_RightVector * ((((unsigned int)direction & (unsigned int)MoveDirection::Left) ? m_Settings.speed : 0.f) * velocity); //left
	}

	void PerspectiveCamera::UpdateProjection(float width, float height)
	{
		m_Settings.apectRatio = width / height;
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Settings.fov), m_Settings.apectRatio, m_Settings.nearPlane, m_Settings.farPlane);
	}

	void PerspectiveCamera::UpdateVectors()
	{
		//rotation vector...
		//pitch, roll, yaw

		//forward vector recalculation
		glm::vec3 tempForward;
		tempForward.x = cos(glm::radians(m_EulerRotation.y)) * cos(glm::radians(m_EulerRotation.x));
		tempForward.y = sin(glm::radians(m_EulerRotation.x));
		tempForward.z = sin(glm::radians(m_EulerRotation.y)) * cos(glm::radians(m_EulerRotation.x));
		m_ForwardVector = glm::normalize(tempForward);

		//update the new right and up vectors as well
		m_RightVector = CalculateRightVector();
		m_UpVector = CalculateUpVector();
	}

	void PerspectiveCamera::UpdateRotation(const glm::vec3& newRotation)
	{
		//QUATERNION STUFF
		/*
		glm::vec3 halfAngles = glm::vec3(newRotation.x / 2, newRotation.y / 2, newRotation.z / 2);
		glm::vec3 cosAngles = cos(halfAngles);
		glm::vec3 sinAngles = sin(halfAngles);
		float w = (cosAngles.z * cosAngles.x * cosAngles.y) + (sinAngles.z * sinAngles.x * sinAngles.y);
		float x = (sinAngles.z * cosAngles.x * cosAngles.y) - (cosAngles.z * sinAngles.x * sinAngles.y);
		float y = (cosAngles.z * sinAngles.x * cosAngles.y) + (sinAngles.z * cosAngles.x * sinAngles.y);
		float z = (cosAngles.z * cosAngles.x * sinAngles.y) - (sinAngles.z * sinAngles.x * cosAngles.y);
		m_Rotation = glm::quat(w, x, y, z); */

		m_EulerRotation = newRotation;
	}

	void PerspectiveCamera::ProcessRotation(const glm::vec2& mouseDelta, bool constrainPitch)
	{
		//x yaw, y pitch
		const glm::vec2 calculatedDelta = mouseDelta * m_Settings.sensitivity;

		m_EulerRotation.y += calculatedDelta.x;
		m_EulerRotation.x += calculatedDelta.y;

		if (constrainPitch)
		{
			if (m_EulerRotation.x > 89.f) m_EulerRotation.x = 89.f;
			if (m_EulerRotation.x < -89.f) m_EulerRotation.x = -89.f;
		}

		UpdateVectors();
	}

	void PerspectiveCamera::SetFov(float fov)
	{
		m_Settings.fov = fov;
		UpdateProjection((unsigned short)Application::GetWindow()->GetWidth(), (unsigned short)Application::GetWindow()->GetHeight());
	}

	glm::vec3 PerspectiveCamera::CalculateUpVector() const
	{
		return glm::normalize(glm::cross(m_RightVector, m_ForwardVector));
	}

	glm::vec3 PerspectiveCamera::CalculateRightVector() const
	{
		return glm::normalize(glm::cross(m_ForwardVector, m_WorldUpVector));
	}

}