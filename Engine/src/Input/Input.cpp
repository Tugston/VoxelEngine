#include "Input.h"

//ENGINE
#include "Core/Application.h"

namespace Engine
{
	bool InputSystem::Init()
	{
		//initialize glfw
		if (glfwInit() == GL_FALSE)
		{
			Logger::LogMessage(Logger::LogType::Critical, "<Input.cpp> glfw Failed To Initialize!");
			return false;
		}

		return true;
	}

	bool InputSystem::KeyPressed(EngineKeys key)
	{
		auto keyState = glfwGetKey(Application::GetWindow()->GetGLFWWindow(), (int)key);
		return keyState == GLFW_PRESS;
	}

	bool InputSystem::KeyReleased(EngineKeys key)
	{
		auto keyState = glfwGetKey(Application::GetWindow()->GetGLFWWindow(), (int)key);
		return keyState == GLFW_RELEASE;
	}

	
}
