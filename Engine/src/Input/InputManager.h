#pragma once

//ENGINE
#include "Input/InputEvents.h"

//STND
#include <stack>
#include <memory>

namespace Engine
{
	class InputManager
	{
	public:
		static bool Init();

		static void ProcessEvents();

	private:
		static std::stack<std::unique_ptr<InputEvent>> s_KeyEvents;
	};
}