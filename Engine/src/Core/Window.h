/*
* File: Window.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-25 (yyyy/mm/dd)
*
* Description: Wrapper for GLFW window and supporting functions
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGINE
#include "Core/Core.h"

//STND
#include <string>

struct GLFWwindow;

namespace Engine
{
	using WindowResizeCallback = std::function<void(int, int)>;

	class Window
	{
	public:
		Window();
		Window(const std::string& name);
		Window(const std::string& name, unsigned short width, unsigned short height);
		~Window();

		inline unsigned short GetWidth() const { return m_Info.width; };
		inline unsigned short GetHeight() const { return m_Info.height; };
		inline std::string_view GetName() const { return m_Info.name; };
		inline GLFWwindow* GetGLFWWindow() const { return m_RenderWindow; };

		
		void PollEvents();
		void DestroyWindow();
		void SwapBuffers();

		//resize callback
		void SetFrameSize(WindowResizeCallback callbackFunction);

		inline const WindowResizeCallback GetResizeCallback() { return m_Info.resizeCallback; };
		inline const std::pair<int, int> GetBufferSize() { return m_Info.bufferSize; };

	private:
		void SetupWindow();
		void InitializeGLFW(); //to allow the window to be created in any order, probably not the best to Initialize glfw multiple times though

	private:
		GLFWwindow* m_RenderWindow;

		//struct for glfw user pointer
		struct WindowInfo
		{
		public:
			std::string name = "Voxel Game";
			unsigned short width = 800;
			unsigned short height = 500;
			WindowResizeCallback resizeCallback; //store the resize callback for the future
			std::pair<int, int> bufferSize;
		};

		WindowInfo m_Info;
	};
}