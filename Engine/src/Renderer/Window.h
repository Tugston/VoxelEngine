#pragma once

//VENDOR
#include <glfw/glfw3.h>

//STND
#include <memory>
#include <string>

namespace Engine
{
	class Window
	{
	public:
		Window();
		Window(const std::string& name);
		Window(const std::string& name, unsigned short width, unsigned short height);
		~Window();

		inline unsigned short GetWidth() const { return m_Width; };
		inline unsigned short GetHeight() const { return m_Height; };

		void SwapBuffer();
		void Draw();

	private:
		void SetupWindow(const std::string& name);

	private:
		GLFWwindow* m_RenderWindow;
		std::string m_Name = "Voxel Game";
		unsigned short m_Width = 800;
		unsigned short m_Height = 500;
	};

}