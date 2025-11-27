#include "egpch.h"
#include "PerspectiveCamera.h"

//ENGINE
#include "Core/Application.h"


namespace Engine::Camera
{
	PerspectiveCamera::PerspectiveCamera()
	{
		m_Settings.fov = 90;
		const Engine::Window* window = Application::GetWindow();
		UpdateProjection(window->GetWidth(), window->GetHeight());
	}

	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position) :
		EditorCamera(position)
	{
		m_Settings.fov = 90;
		const Engine::Window* window = Application::GetWindow();
		UpdateProjection(window->GetWidth(), window->GetHeight());
	}

	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, UINT8 fov) :
		EditorCamera(position)
	{
		m_Settings.fov = fov;
		const Engine::Window* window = Application::GetWindow();
		UpdateProjection(window->GetWidth(), window->GetHeight());
	}

	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, const glm::vec3& rotation, UINT8 fov, float speed) :
		EditorCamera(position, rotation, speed)
	{
		m_Settings.fov = fov;
		const Engine::Window* window = Application::GetWindow();
		UpdateProjection(window->GetWidth(), window->GetHeight());
	}

	void PerspectiveCamera::ProcessLocation(MoveDirection direction, float deltaTime)
	{
		float velocity = m_Settings.speed * deltaTime;

		//this can be basic multiplication instead of if checks, plus want to get rid of the c casts
		m_Location += m_ForwardVector * ((((unsigned int)direction & (unsigned int)MoveDirection::Forward) ? m_Settings.speed : 0.f) * velocity); //forward
		m_Location -= m_ForwardVector * ((((unsigned int)direction & (unsigned int)MoveDirection::Backwards) ? m_Settings.speed : 0.f) * velocity); //backwards
		m_Location += m_RightVector * ((((unsigned int)direction & (unsigned int)MoveDirection::Right) ? m_Settings.speed : 0.f) * velocity); //right
		m_Location -= m_RightVector * ((((unsigned int)direction & (unsigned int)MoveDirection::Left) ? m_Settings.speed : 0.f) * velocity); //left
	}

	void PerspectiveCamera::UpdateProjection(float width, float height)
	{
		m_Settings.apectRatio = width / height;
		m_ProjectionMatrix = glm::perspective(static_cast<float>(glm::radians((float)m_Settings.fov)), m_Settings.apectRatio, m_Settings.nearPlane, m_Settings.farPlane);
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
		UpdateProjection(Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight());
	}
}