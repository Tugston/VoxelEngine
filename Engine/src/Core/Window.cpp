/*
* File: Window.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-25 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Window.h"

//VENDOR
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

//ENGINE
#include "Core/Logger.h"

//STND
#include <cassert>
#include <dwmapi.h>

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
		DestroyWindow();
	}

	void Window::SetWindowBorderColor(const Maths::Vector3<float>& color) const
	{
		if (!m_RenderWindow) return;
		HWND hwnd = glfwGetWin32Window(m_RenderWindow);
		if (!&hwnd) return; //just ensuring this window is valid

		LOG_MSG("<Window.cpp> (SetWindowBorderColor) Setting Border Color To: ({}, {}, {})", color.x, color.y, color.z);

		COLORREF borderColor = static_cast<COLORREF>(RGBtoHex(color));
		DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &borderColor, sizeof(borderColor));
	}

	void Window::SetWindowHeadingColor(const Maths::Vector3<float>& color) const
	{
		if (!m_RenderWindow) return;
		HWND hwnd = glfwGetWin32Window(m_RenderWindow);
		if (!&hwnd) return; //just ensuring this window is valid

		LOG_MSG("<Window.cpp> (SetWindowHeadingColor) Setting Heading Color To: ({}, {}, {})", color.x, color.y, color.z);

		COLORREF headingColor = static_cast<COLORREF>(RGBtoHex(color));
		DwmSetWindowAttribute(hwnd, DWMWA_CAPTION_COLOR, &headingColor, sizeof(headingColor));
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::DestroyWindow()
	{
		glfwDestroyWindow(m_RenderWindow);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_RenderWindow);
	}

	void Window::SetFrameSize(WindowResizeCallback callbackFunction)
	{
		m_Info.resizeCallback = std::move(callbackFunction);

		glfwSetFramebufferSizeCallback(m_RenderWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowInfo* data = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
				if (data)
				{
					data->resizeCallback(width, height); //call the stored function
				}
			});
	}

	void Window::SetupWindow()
	{
		Logger::LogMessage(Logger::LogType::Message, "Initializing Window...");	

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); //remove decoration for full screen and windowed borderless, add it back for windowed

		m_RenderWindow = glfwCreateWindow(m_Info.width, m_Info.height, m_Info.name.c_str(), NULL, NULL);

		if (!m_RenderWindow)
		{
			glfwTerminate();
			Logger::LogMessage(Logger::LogType::Critical, "<Window.cpp> glfw Did Not Create Window!");
			EG_ASSERT(false);
		}

		//buffer size
		glfwGetFramebufferSize(m_RenderWindow, &m_Info.bufferSize.first, &m_Info.bufferSize.second);

		glfwMakeContextCurrent(m_RenderWindow);
		glfwSetWindowUserPointer(m_RenderWindow, &m_Info);

		//enable / disable vsync
		glfwSwapInterval(1);

		Logger::LogMessage(Logger::LogType::Message, "Window Created...");
	}

	void Window::InitializeGLFW()
	{
		if (glfwInit() == GLFW_FALSE)
		{
			Logger::LogMessage(Logger::LogType::Critical, "<Window.cpp> glfw Is Not Initialized!");
			EG_ASSERT(false);
		}
	}

	unsigned int Window::RGBtoHex(const Maths::Vector3<float>& color) const
	{
		const char r = (std::max)(0.f, (std::min)(255.f, color.x));
		const char g = (std::max)(0.f, (std::min)(255.f, color.y));
		const char b = (std::max)(0.f, (std::min)(255.f, color.z));
		return (b << 16) || (g << 16) || r;
	}
}