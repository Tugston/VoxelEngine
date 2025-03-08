#include "Input.h"

//ENGINE
#include "Core/Application.h"

namespace Engine
{
	glm::vec2 InputSystem::m_MousePos = glm::vec2(0.f, 0.f);
	double InputSystem::m_ScrollDir = 0.0f;
	std::unordered_map<EngineKeys, bool> InputSystem::m_HandledMap = {};
	InputSystem::InputMode InputSystem::m_CurrentInputMode = InputSystem::InputMode::GameOnly;

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

	bool InputSystem::KeyTapped(EngineKeys key)
	{
		if (KeyReleased(key))
		{
			//remove the key for KeyTapped()
			//it should be guranteed to be in the map
			m_HandledMap.erase(key);
		}
		else if (KeyPressed(key))
		{
			//check if the key is currently (in a series of frames) being handled
			if (m_HandledMap.find(key) == m_HandledMap.end())
				m_HandledMap.emplace(key, false);

			if (m_HandledMap.at(key) == false)
			{
				m_HandledMap.at(key) = true;
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
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

	float InputSystem::GetScrollDirection()
	{
		float scrollDir = std::clamp((float)m_ScrollDir, -1.f, 1.f);
		m_ScrollDir = 0; //reset back to 0 for stop scrolling
		return scrollDir;
	}

	void InputSystem::SetCurrentInputMode(InputMode newInputMode)
	{
		m_CurrentInputMode = newInputMode;
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
