#pragma once

//ENGINE
#include "Input/KeyDefines.h"
#include "Core/Logger.h"

//STND
#include <unordered_map>

//VENDOR
#include <glm/glm.hpp>

struct GLFWwindow;


//TRYING TO GET THE MOUSE MOVE DIRECTION WORKING, SO THAT I CAN CONTROL THE CAMERA TO SEE WHERE THE QUAD IS LOCATED THAT THE RENDERER IS TEMPORARILY DRAWING

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

		//bit flag
		static enum class MouseMoveDirection
		{
			Stationary = 0,		//storing as char and enum is uint obviously, so just handling the 0 manually to avoid cast
			Left	   = 1 << 0,	//0001
			Right	   = 1 << 1,	//0010
			Up		   = 1 << 2,	//0100
			Down	   = 1 << 3		//1000
		};

	public:
		static bool Init();

		//polls the first frame the key is pressed
		//resets once key is released
		static bool KeyTapped(EngineKeys key);

		//polls the entire time the key is held
		static bool KeyPressed(EngineKeys key);
		static bool KeyReleased(EngineKeys key);

		static glm::vec2 GetMousePos();
		static glm::vec2 GetMouseDelta();
		static float GetMouseX();
		static float GetMouseY();

		static void SetPreviousMousePos(const glm::vec2& pos);

		static float GetScrollDirection();

		static void SetCurrentInputMode(InputMode newInputMode);
		static inline InputMode GetInputMode() { return m_CurrentInputMode; };

		//returns the current byte data of the mouse position
		static inline char GetRawMouseDirection() { return m_MouseDirection; };

		static void MouseIdleDetection(float deltaTime);

	private:
		static void MousePositionCallBack(GLFWwindow* window, double x, double y);
		static void ScrollWheelCallBack(GLFWwindow* window, double x, double y);

		static glm::vec2 m_MousePos;
		static glm::vec2 m_PreviousMousePos;
		static unsigned char m_MouseMoveTolerance;	//screen coords are posotive whole numbers

		//can store the direction data in a byte
		static unsigned char m_MouseDirection;

		//idle mouse time
		static float m_IdleTime;

		static double m_ScrollDir;

		//determines if the input was handled or not
		static std::unordered_map<EngineKeys, bool> m_HandledMap;
		
			
		static InputMode m_CurrentInputMode;
	};
}

//these appropriately simplify the api ( imo :/ )
#define ENGINE_MOUSE_IDLE	Engine::InputSystem::GetRawMouseDirection() == 0
#define ENGINE_MOUSE_UP		Engine::InputSystem::GetRawMouseDirection() & (char)Engine::InputSystem::MouseMoveDirection::Up
#define ENGINE_MOUSE_DOWN	Engine::InputSystem::GetRawMouseDirection() & (char)Engine::InputSystem::MouseMoveDirection::Down
#define ENGINE_MOUSE_LEFT	Engine::InputSystem::GetRawMouseDirection() & (char)Engine::InputSystem::MouseMoveDirection::Left
#define ENGINE_MOUSE_RIGHT  Engine::InputSystem::GetRawMouseDirection() & (char)Engine::InputSystem::MouseMoveDirection::Right