#pragma once

//ENGINE
#include "KeyDefines.h"
#include "Core/Core.h"
#include "Core/Logger.h"

//STND
#include <memory>
#include <map>

//VENDOR
#include <glm/glm.hpp>
#include <glfw/glfw3.h>

namespace Engine
{

	class ENGINE_API InputSystem
	{
	public:
		static bool Init();
		static bool KeyPressed(EngineKeys key);
		static bool KeyReleased(EngineKeys key);

		static glm::vec2 GetMousePos();
		static float GetMouseX();
		static float GetMouseY();

	private:
		static void MousePositionCallBack(GLFWwindow* window, double x, double y);
		static void ScrollWheelCallBack(GLFWwindow* window, double x, double y);

		static glm::vec2 m_MousePos;
		static double m_ScrollDir;
	};
}