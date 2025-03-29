#pragma once

//ENGINE
#include "Renderer/Architecture/Camera/CameraSettings.h"


namespace Engine::Renderer{

	class PerspectiveCamera
	{
	public:
		//vec3 rotation is just an easy way to store the data, it is not trying to be a rotation matrix
		//rotation = (pitch, roll, yaw)
		PerspectiveCamera(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& forwardVector, float fov, float speed);

		PerspectiveCamera(const glm::vec3& position, float fov, const glm::vec3& forwardVector);
		PerspectiveCamera(const glm::vec3& position, float fov);
		PerspectiveCamera(const glm::vec3& position);
		~PerspectiveCamera() {};

		void Update(glm::vec3 direction, glm::vec3 rotationAxis, float deltaTime);

		void SetFov(float fov);

		void SetSpeed(float speed) { m_Settings.speed = speed; };
		void SetSensitivity(float sensitivity) { m_Settings.sensitivity = sensitivity; };

		const inline glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Location, m_Location + m_ForwardVector, m_UpVector); };
		const inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; };

		const inline glm::vec3 GetForwardVector() const { return m_ForwardVector; };
		
		//returns normalized
		const inline glm::vec3 GetUpVector() const { return m_UpVector; };
		const inline glm::vec3 GetRightVector() const { return m_RightVector; };
		

	private:
		glm::vec3 CalculateUpVector() const;
		glm::vec3 CalculateRightVector() const;

		//helper function that easily allows camera settings to change
		void UpdateProjection();
	
	private:
		Settings::CameraSettings m_Settings;
		
		glm::quat m_Rotation = glm::quat(glm::vec3(0.f, 0.f, 0.f));
		glm::vec3 m_Location;

		glm::vec3 m_ForwardVector = glm::vec3(1, 0, 0);
		glm::vec3 m_RightVector;
		glm::vec3 m_UpVector;
	
		glm::mat4 m_ProjectionMatrix;
	};

}
