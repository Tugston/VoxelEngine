#include "Window.h"

//ENGINE
#include "Core/Logger.h"

namespace Engine
{
	Window::Window()
	{
		SetupWindow(m_Name);
	}

	Window::Window(const std::string& name)
	{
		SetupWindow(name);
	}

	Window::Window(const std::string& name, unsigned short width, unsigned short height) :
		m_Width(width), m_Height(height)
	{
		SetupWindow(name);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_RenderWindow);
	}

	void Window::SwapBuffer()
	{
		glfwSwapBuffers(m_RenderWindow);
	}

	void Window::Draw()
	{
	}

	void Window::SetupWindow(const std::string& name)
	{
		Logger::LogMessage(Logger::LogType::Message, "Window Initializing...");

		m_RenderWindow = glfwCreateWindow(m_Width, m_Height, name.c_str(), NULL, NULL);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (m_RenderWindow)
		{
			Logger::LogMessage(Logger::LogType::Message, "Window \"{}\" Initialized", name);
		}
		else
		{
			Logger::LogMessage(Logger::LogType::Critical, "Window \"{}\" Failed To Initialized", name);
		}

		glfwMakeContextCurrent(m_RenderWindow);
	}
}