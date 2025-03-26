#pragma once

//ENGINE
#include "Input/KeyDefines.h"
#include "Core/Logger.h"

//STND
#include <unordered_map>

//VENDOR
#include <glm/glm.hpp>

struct GLFWwindow;

namespace Engine
{

	class InputSystem
	{
	public:
		static enum class InputMode
		{
			GameOnly = 0,
			GameAndUI,
			UIOnly,
			Debug
		};

		static enum class ScrollDirection
		{
			Up = 1,
			Down = -1
		};

	public:
		static bool Init();

		//polls the first frame the key is held
		//resets once key is released
		static bool KeyTapped(EngineKeys key);

		//polls the entire time the key is held
		static bool KeyPressed(EngineKeys key);
		static bool KeyReleased(EngineKeys key);

		static glm::vec2 GetMousePos();
		static float GetMouseX();
		static float GetMouseY();

		static float GetScrollDirection();

		static void SetCurrentInputMode(InputMode newInputMode);
		static inline InputMode GetInputMode() { return m_CurrentInputMode; };

	private:
		static void MousePositionCallBack(GLFWwindow* window, double x, double y);
		static void ScrollWheelCallBack(GLFWwindow* window, double x, double y);

		static glm::vec2 m_MousePos;
		static double m_ScrollDir;

		//determines if the input was handled or not
		static std::unordered_map<EngineKeys, bool> m_HandledMap;
		
			
		static InputMode m_CurrentInputMode;
	};
}