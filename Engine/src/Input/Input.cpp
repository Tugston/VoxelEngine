#include "Input.h"

//ENGINE
#include "Application.h"

namespace Engine
{
	

	bool InputSystem::Init()
	{

		//initialize glfw
		if (!glfwInit())
		{
			return false;
		};

		return true;
	}

	bool InputSystem::KeyPressed(EngineKeys key)
	{
		Window* window = Application::GetWindow();

		auto keyState = glfwGetKey(window->GetGLFWWindow(), static_cast<int>(key));
		return keyState == GLFW_PRESS;
	}

	bool InputSystem::KeyReleased(EngineKeys key)
	{
		Window* window = Application::GetWindow();

		auto keyState = glfwGetKey(window->GetGLFWWindow(), static_cast<int>(key));
		return keyState == GLFW_RELEASE;
	}
}
