#pragma once

//VENDOR
#include <glfw/glfw3.h>

namespace Engine
{
	enum class EngineKeys
	{
		//coorelate supported keys to glfw's key system
		LeftClick	=		GLFW_MOUSE_BUTTON_1,
		RightClick  =		GLFW_MOUSE_BUTTON_2,
		W			=		GLFW_KEY_W,
		A			=		GLFW_KEY_A,
		S			=		GLFW_KEY_S,
		D			=		GLFW_KEY_D,
		Space		=		GLFW_KEY_SPACE,
		Enter		=		GLFW_KEY_ENTER,
		BackSpace	=		GLFW_KEY_BACKSPACE
	};

	enum class KeyState
	{
		Pressed,		//key was just pressed on the current frame
		Released,		//key was just released on the current frame
		Held,			//key is being held down across multiple frames
		Moved,			//key (mouse) is being moved on the current frame
		Scrolled		//key (mouse) is being scrolled on the current frame
	};
}