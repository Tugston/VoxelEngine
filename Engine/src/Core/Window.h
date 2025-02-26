#pragma once

//ENGINE
#include "Core/Core.h"
#include "Input/MouseEvent.h"

//STND
#include <string>


struct GLFWwindow;

namespace Engine
{

	class ENGINE_API Window
	{
	public:
		using Event_FN = std::function<void(CallBackEvent&)>;
	public:
		Window();
		Window(const std::string& name);
		Window(const std::string& name, unsigned short width, unsigned short height);
		~Window();

		inline unsigned short GetWidth() const { return m_Info.width; };
		inline unsigned short GetHeight() const { return m_Info.height; };
		inline GLFWwindow* GetGLFWWindow() const { return m_RenderWindow; };

		void SetEventCallback(const Event_FN& callback) { m_Info.eventCallBack = callback; };

		void Draw();
		void PollEvents();


	private:
		void SetupWindow();
		void InitializeGLFW(); //to allow the window to be created in any order

	private:
		GLFWwindow* m_RenderWindow;

		struct WindowInfo
		{
		public:
			std::string name = "Voxel Game";
			unsigned short width = 800;
			unsigned short height = 500;
			Event_FN eventCallBack;
		};

		WindowInfo m_Info;

	};
}