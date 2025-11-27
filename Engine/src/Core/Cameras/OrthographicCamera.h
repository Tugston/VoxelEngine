#pragma once

#include "EditorCamera.h"

//WIP - not important right now

namespace Engine::Camera
{
	class OrthographicCamera : public EditorCamera {
	public:
		OrthographicCamera();
		~OrthographicCamera();
	};
}
