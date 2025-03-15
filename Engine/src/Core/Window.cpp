#include "Window.h"

//VENDOR
#include <GL/glew.h>
#include <glfw/glfw3.h>

//ENGINE
#include "Core/Logger.h"

//STND
#include <cassert>

namespace Engine
{
	Window::Window()
	{
		InitializeGLFW();
		SetupWindow();
	}

	Window::Window(const std::string& name)
	{
		m_Info.name = name;

		InitializeGLFW();
		SetupWindow();
	}

	Window::Window(const std::string& name, unsigned short width, unsigned short height) 
	{
		m_Info.name = name;
		m_Info.width = width;
		m_Info.height = height;

		InitializeGLFW();
		SetupWindow();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_RenderWindow);
	}

	void Window::Clear()
	{
		glClearColor(.5f, .9f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
	//	glfwSwapBuffers(m_RenderWindow);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::SetupWindow()
	{
		Logger::LogMessage(Logger::LogType::Message, "Initializing Window...");

		//window properties
		m_RenderWindow = glfwCreateWindow(m_Info.width, m_Info.height, m_Info.name.c_str(), NULL, NULL);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_CURSOR_HIDDEN, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


		if (!m_RenderWindow)
		{
			glfwTerminate();
			Logger::LogMessage(Logger::LogType::Critical, "<Window.cpp> glfw Did Not Create Window!");
			EG_ASSERT(false);
		}

		//buffer size
		int bufferWidth, bufferHeight;
		glfwGetFramebufferSize(m_RenderWindow, &bufferWidth, &bufferHeight);

		glfwMakeContextCurrent(m_RenderWindow);
		glfwSetWindowUserPointer(m_RenderWindow, &m_Info);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			glfwDestroyWindow(m_RenderWindow);
			glfwTerminate();
			Logger::LogMessage(Logger::LogType::Critical, "<Window.cpp> glew Did Not Initialize!");
			EG_ASSERT(false);
		}

		glViewport(0, 0, bufferWidth, bufferHeight);

		//enable / disable vsync
		glfwSwapInterval(1);

		Logger::LogMessage(Logger::LogType::Message, "Window Created...");
	}

	void Window::InitializeGLFW()
	{
		if (glfwInit() == GL_FALSE)
		{
			Logger::LogMessage(Logger::LogType::Critical, "<Window.cpp> glfw Is Not Initialized!");
			EG_ASSERT(false);
		}
	}
}