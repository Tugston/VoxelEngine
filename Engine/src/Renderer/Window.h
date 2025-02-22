#pragma once


//STND
#include <memory>
#include <string>

class GLFWwindow;

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
		inline GLFWwindow* GetGLFWWindow() const { return m_RenderWindow; };

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