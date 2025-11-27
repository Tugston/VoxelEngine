#pragma once

#include "CameraSettings.h"

namespace Engine::Camera
{
	class EditorCamera {
	protected:
		EditorCamera();
		EditorCamera(const glm::vec3& position);
		EditorCamera(const glm::vec3& position, const glm::vec3& rotation, float speed);

		//temporarily public for testing, needs to be protected!
	public:
		enum class MoveDirection: UINT8
		{
			Forward = 1 << 0,
			Backwards = 1 << 2,
			Left = 1 << 3,
			Right = 1 << 4
		};
	
	public:
		virtual void ProcessRotation(const glm::vec2& mouseDelta, bool constrainPitch) = 0;
		virtual void ProcessLocation(MoveDirection direction, float deltaTime) = 0;
		virtual void UpdateProjection(float width, float height) = 0;


		void SetSpeed(float speed) { m_Settings.speed = speed; }
		void SetSensitivity(float sensitivity) { m_Settings.sensitivity = sensitivity; }
		
		glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Location, m_Location + m_ForwardVector, m_UpVector); }
		glm::vec3 GetForwardVector() const { return m_ForwardVector; }
		glm::vec3 GetUpVector() const { return m_UpVector; } //returns normalized
		glm::vec3 GetRightVector() const { return m_RightVector; } //returns normalized
		glm::vec3 GetEulerRotation() const { return m_EulerRotation; }
		glm::quat GetQuatRotation() const { return m_Rotation; }
		CameraSettings GetSettings() const { return m_Settings; }

	protected:
		void UpdateVectors();
	private:
		void UpdateRotation(const glm::vec3& newRotation);

		glm::vec3 CalculateUpVector() const;
		glm::vec3 CalculateRightVector() const;

	protected:
		CameraSettings m_Settings;

		glm::quat m_Rotation = glm::quat(glm::vec3(0.f, 0.f, 0.f));
		glm::vec3 m_EulerRotation = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 m_Location;

		glm::vec3 m_ForwardVector = glm::vec3(0.f, 0.f, -1.f);
		glm::vec3 m_RightVector;
		glm::vec3 m_UpVector = glm::vec3(0.f, 1.f, 0.f);

		glm::mat4 m_ProjectionMatrix;
	};
}


