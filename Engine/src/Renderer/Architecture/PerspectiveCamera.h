#pragma once

//VENDOR
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine::Renderer{

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov, const glm::vec3& forwardVector, float nearPlane, float farPlane, float aspectRatio = 16/9);
		~PerspectiveCamera() {};

		//helper function that easily allows camera settings to change
		void UpateProjection();

		void SetFov(float fov);
		void SetViewDistance(float distance);
		void SetAspectRatio(float aspectRatio);

		inline glm::mat4 GetViewMatrix(const glm::vec3& position) const { return glm::lookAt(position, m_ForwardVector, GetUpVector()); };
		inline glm::vec3 GetForwardVector() { return m_ForwardVector; };
		
		glm::vec3 GetUpVector() const;
		glm::vec3 GetRightVector() const;
		

	private:
		float m_Fov;

		glm::vec3 m_ForwardVector;
	
		float m_NearPlane;
		float m_FarPlane;
		float m_AspectRatio;

		glm::mat4 m_ProjectionMatrix;
	};

}
