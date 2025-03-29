#include "egpch.h"
#include "PerspectiveCamera.h"

//ENGINE
#include "Core/Application.h"

namespace Engine::Renderer
{
	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& forwardVector, float fov, float speed) :
		m_Settings(2.f, fov, speed), m_Location(position), m_ForwardVector(forwardVector)
	{
		UpdateProjection();
		m_RightVector = CalculateRightVector();
		m_UpVector = CalculateRightVector();
	}

	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, float fov, const glm::vec3& forwardVector) :
		m_Settings(fov), m_Location(position), m_ForwardVector(forwardVector)
	{
		UpdateProjection();
		m_RightVector = CalculateRightVector();
		m_UpVector = CalculateUpVector();
	}

	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, float fov) :
		m_Settings(fov), m_Location(position)
	{
		UpdateProjection();
		m_RightVector = CalculateRightVector();
		m_UpVector = CalculateUpVector();
	}

	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position) :
		m_Location(position)
	{
		UpdateProjection();
		m_RightVector = CalculateRightVector();
		m_UpVector = CalculateUpVector();
	}

	void PerspectiveCamera::Update(glm::vec3 direction, glm::vec3 rotationAxis, float deltaTime)
	{
		float velocity = m_Settings.speed * deltaTime;
		m_Location += direction * velocity;
	
		float rotationAmnt = m_Settings.sensitivity * deltaTime;
		m_Rotation = glm::angleAxis(glm::radians(rotationAmnt), rotationAxis) * m_Rotation;

	//	Logger::LogMessage(Logger::LogType::Message, "Camera Rotation: {}, {}, {}", m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//	Logger::LogMessage(Logger::LogType::Message, "Camera Position: {}, {}, {}", m_Location.x, m_Location.y, m_Location.z);
	}

	void PerspectiveCamera::UpdateProjection()
	{
		float aspectRatio = Application::GetWindow()->GetWidth() / Application::GetWindow()->GetHeight();
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Settings.fov), aspectRatio, m_Settings.nearPlane, m_Settings.farPlane);
	}

	void PerspectiveCamera::SetFov(float fov)
	{
		m_Settings.fov = fov;
		UpdateProjection();
	}

	glm::vec3 PerspectiveCamera::CalculateUpVector() const
	{
		return glm::normalize(glm::cross(m_ForwardVector, m_RightVector));
	}

	glm::vec3 PerspectiveCamera::CalculateRightVector() const
	{
		return glm::normalize(glm::cross(m_UpVector, m_ForwardVector));
	}

}