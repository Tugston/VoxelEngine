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

	void Window::Draw()
	{
		glClearColor(.5f, .9f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_RenderWindow);
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
			assert(false);
		}

		//buffer size
		int bufferWidth, bufferHeight;
		glfwGetFramebufferSize(m_RenderWindow, &bufferWidth, &bufferHeight);

		glfwMakeContextCurrent(m_RenderWindow);
		glfwSetWindowUserPointer(m_RenderWindow, &m_Info);

		//setup the callbacks for events
		glfwSetCursorPosCallback(m_RenderWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowInfo& data = *(WindowInfo*)glfwGetWindowUserPointer(window);

				MouseMoveEvent event((float)xPos, (float)yPos);
				data.eventCallBack(event);
			});

		glfwSetScrollCallback(m_RenderWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowInfo& data = *(WindowInfo*)glfwGetWindowUserPointer(window);
				
				//I do not want to support horizontal mouse scroll wheel movement, so I am just not going to use the xOffset
				//I get an error if I don't include it :(
				MouseScrollEvent event((float)yOffset);
				data.eventCallBack(event);
			});


		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			glfwDestroyWindow(m_RenderWindow);
			glfwTerminate();
			Logger::LogMessage(Logger::LogType::Critical, "<Window.cpp> glew Did Not Initialize!");
			assert(false);
		}

		glViewport(0, 0, bufferWidth, bufferHeight);

		Logger::LogMessage(Logger::LogType::Message, "Window Created...");
	}

	void Window::InitializeGLFW()
	{
		if (glfwInit() == GL_FALSE)
		{
			Logger::LogMessage(Logger::LogType::Critical, "<Window.cpp> glfw Is Not Initialized!");
			assert(false);
		}
	}
}