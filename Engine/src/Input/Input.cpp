#include "egpch.h"
#include "Input/Input.h"

//ENGINE
#include "Core/Application.h"

#include <GL/GL.h>

namespace Engine
{
	unsigned char InputSystem::m_MouseMoveTolerance = 1;

	glm::vec2 InputSystem::m_MousePos = glm::vec2(0.f, 0.f);
	glm::vec2 InputSystem::m_PreviousMousePos = glm::vec2(0.f, 0.f);
	unsigned char InputSystem::m_MouseDirection = 0;
	double InputSystem::m_ScrollDir = 0.f;
	float InputSystem::m_IdleTime = 0.f;
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

	glm::vec2 InputSystem::GetMouseDelta()
	{
		return m_MousePos - m_PreviousMousePos;
	}

	float InputSystem::GetMouseX()
	{
		return m_MousePos.x;
	}

	float InputSystem::GetMouseY()
	{
		return m_MousePos.y;
	}

	void InputSystem::SetPreviousMousePos(const glm::vec2& pos)
	{
		m_PreviousMousePos = pos;
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

	void InputSystem::MouseIdleDetection(float deltaTime)
	{
		m_IdleTime += deltaTime;

		if (m_IdleTime >= 0.1)
			m_MouseDirection = 0;
	}

	void InputSystem::MousePositionCallBack(GLFWwindow* window, double x, double y)
	{

		//reset the mouse state each call
		//unless there is a way to detect the last callback call and just set the direction stationary then
		m_MouseDirection = 0;

		//reset the idle time
		m_IdleTime = 0.f;

		m_PreviousMousePos = m_MousePos;
		m_MousePos = { (float)x, (float)y };

		glm::vec2 delta = GetMouseDelta();

		if (delta.x < -m_MouseMoveTolerance) m_MouseDirection |= (char)MouseMoveDirection::Left;
		else if (delta.x > m_MouseMoveTolerance) m_MouseDirection |= (char)MouseMoveDirection::Right;

		if (delta.y > m_MouseMoveTolerance) m_MouseDirection |= (char)MouseMoveDirection::Down;
		else if (delta.y < -m_MouseMoveTolerance) m_MouseDirection |= (char)MouseMoveDirection::Up;
	}

	void InputSystem::ScrollWheelCallBack(GLFWwindow* window, double x, double y)
	{
		//X is not useful for this engine
		m_ScrollDir = (float)y;
	}

	
}
