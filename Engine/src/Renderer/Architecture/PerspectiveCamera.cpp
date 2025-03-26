#include "egpch.h"
#include "PerspectiveCamera.h"

namespace Engine::Renderer
{
	PerspectiveCamera::PerspectiveCamera(float fov, const glm::vec3& forwardVector, float nearPlane, float farPlane, float aspectRatio) :
		m_Fov(fov), m_ForwardVector(forwardVector), m_NearPlane(nearPlane), m_FarPlane(farPlane), m_AspectRatio(aspectRatio)
	{
		UpateProjection();
	}

	void PerspectiveCamera::UpateProjection()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearPlane, m_FarPlane);
	}

	void PerspectiveCamera::SetFov(float fov)
	{
		m_Fov = fov;
		UpateProjection();
	}

	void PerspectiveCamera::SetViewDistance(float distance)
	{
		m_FarPlane = distance;
		UpateProjection();
	}

	void PerspectiveCamera::SetAspectRatio(float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
		UpateProjection();
	}
	glm::vec3 PerspectiveCamera::GetUpVector() const
	{
		return glm::vec3();
	}
	glm::vec3 PerspectiveCamera::GetRightVector() const
	{
		return glm::vec3();
	}
	glm::vec3 PerspectiveCamera::GetUpVector()
	{
		return glm::vec3();
	}
	glm::vec3 PerspectiveCamera::GetRightVector()
	{
		return glm::vec3();
	}
}