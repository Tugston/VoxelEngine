#pragma once
#include "PerspectiveCamera.h"
#include "CameraSettings.h"

//Editor Camera

namespace Engine::Renderer{

	//this enum needs to be apart of the ecs
	enum class MoveDirection
	{
		Forward = 1 << 0,
		Backwards = 1 << 2,
		Left = 1 << 3,
		Right = 1 << 4
	};

	//NOTE FOR LATER:
	//MAKE A DEFAULT CONSTRUCTOR, I"M TIRED OF HAVING TO PASS IN 0, 0, 0 POSITION

	class PerspectiveCamera
	{
	public:
		//vec3 rotation is just an easy way to store the data, it is not trying to be a rotation matrix
		//rotation = (pitch, roll, yaw)
		PerspectiveCamera(const glm::vec3& position, const glm::vec3& rotation, float fov, float speed);

		PerspectiveCamera(const glm::vec3& position, float fov);
		PerspectiveCamera(const glm::vec3& position);
		~PerspectiveCamera() {};

		void ProcessLocation(MoveDirection direction, float deltaTime);

		//used for user input controls
		void ProcessRotation(const glm::vec2& mouseDelta, bool constrainPitch);

		void UpdateProjection(float width, float height);

		void SetFov(float fov);

		void SetSpeed(float speed) { m_Settings.speed = speed; };
		void SetSensitivity(float sensitivity) { m_Settings.sensitivity = sensitivity; };

		const inline glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Location, m_Location + m_ForwardVector, m_UpVector); };
		const inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; };

		const inline glm::vec3 GetForwardVector() const { return m_ForwardVector; };
		
		//returns normalized
		const inline glm::vec3 GetUpVector() const { return m_UpVector; };
		const inline glm::vec3 GetRightVector() const { return m_RightVector; };

		const inline glm::vec3 GetEulerRotation() const { return m_EulerRotation; };
		const inline glm::quat GetQuatRotation() const { return m_Rotation; };

		inline Settings::CameraSettings* GetSettings() { return &m_Settings; };
		

	private:
		glm::vec3 CalculateUpVector() const;
		glm::vec3 CalculateRightVector() const;

		//helper functions that easily allows camera settings to change
		void UpdateVectors();
		void UpdateRotation(const glm::vec3& newRotation);
	
	private:
		Settings::CameraSettings m_Settings;
		
		glm::quat m_Rotation = glm::quat(glm::vec3(0.f, 0.f, 0.f));
		glm::vec3 m_EulerRotation = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 m_Location;

		glm::vec3 m_ForwardVector = glm::vec3(0.f, 0.f, -1.f);
		glm::vec3 m_RightVector;
		glm::vec3 m_UpVector = glm::vec3(0.f, 1.f, 0.f);
		glm::vec3 m_WorldUpVector = glm::vec3(0.f, 1.f, 0.f);
	
		glm::mat4 m_ProjectionMatrix;
	};

}
