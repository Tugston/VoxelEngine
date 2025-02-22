#include "Window.h"

//ENGINE
#include "Core/Logger.h"

//VENDOR
#include <GL/glew.h>
#include <glfw/glfw3.h>

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

	void Window::Draw()
	{
		glClearColor(.5f, .9f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_RenderWindow);
	}

	void Window::SetupWindow(const std::string& name)
	{
		Logger::LogMessage(Logger::LogType::Message, "Window Initializing...");

		//window properties
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_CURSOR_HIDDEN, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		m_RenderWindow = glfwCreateWindow(m_Width, m_Height, name.c_str(), NULL, NULL);

		if (!m_RenderWindow)
		{
			Logger::LogMessage(Logger::LogType::Critical, "Could Not Create Window!");
			glfwTerminate();
			assert(true);
		}

		//buffer size
		int bufferWidth, bufferHeight;
		glfwGetFramebufferSize(m_RenderWindow, &bufferWidth, &bufferHeight);

		glfwMakeContextCurrent(m_RenderWindow);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			Logger::LogMessage(Logger::LogType::Critical, "Glew Could Not Initialize!");
			glfwDestroyWindow(m_RenderWindow);
			glfwTerminate();
			assert(true);
		}

		glViewport(0, 0, bufferWidth, bufferHeight);
	}
}