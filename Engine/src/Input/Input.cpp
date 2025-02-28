#include "Input.h"

//ENGINE
#include "Core/Application.h"

namespace Engine
{
	glm::vec2 InputSystem::m_MousePos = glm::vec2(0.f, 0.f);
	double InputSystem::m_ScrollDir = 0.0f;

	bool InputSystem::Init()
	{
		//initialize glfw
		if (glfwInit() == GL_FALSE)
		{
			Logger::LogMessage(Logger::LogType::Critical, "<Input.cpp> glfw Failed To Initialize!");
			return false;
		}

		glfwSetScrollCallback(Application::GetWindow()->GetGLFWWindow(), ScrollWheelCallBack);
		glfwSetCursorPosCallback(Application::GetWindow()->GetGLFWWindow(), MousePositionCallBack);

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

	glm::vec2 InputSystem::GetMousePos()
	{
		return m_MousePos;
	}

	float InputSystem::GetMouseX()
	{
		return m_MousePos.x;
	}

	float InputSystem::GetMouseY()
	{
		return m_MousePos.y;
	}

	void InputSystem::MousePositionCallBack(GLFWwindow* window, double x, double y)
	{
		m_MousePos.x = (float)x;
		m_MousePos.y = (float)y;
	}

	void InputSystem::ScrollWheelCallBack(GLFWwindow* window, double x, double y)
	{
		//X is not useful for this engine
		m_ScrollDir = (float)y;
	}

	
}
