#pragma once
#include "EditorCamera.h"

namespace Engine::Camera
{
	class PerspectiveCamera : public EditorCamera
	{
	public:
		PerspectiveCamera();
		PerspectiveCamera(const glm::vec3& position);
		PerspectiveCamera(const glm::vec3& position, UINT8 fov);
		PerspectiveCamera(const glm::vec3& position, const glm::vec3& rotation, UINT8 fov, float speed);

		~PerspectiveCamera() {};

		virtual void ProcessLocation(MoveDirection direction, float deltaTime) override;
		virtual void ProcessRotation(const glm::vec2& mouseDelta, bool constrainPitch) override;
		virtual void UpdateProjection(float width, float height) override;

		void SetFov(float fov);


	private:
	};
}
