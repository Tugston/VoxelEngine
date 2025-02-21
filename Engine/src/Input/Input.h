#pragma once

//ENGINE
#include "KeyDefines.h"
#include "Core/Core.h"

//STND
#include <memory>

namespace Engine
{
	class InputManager;

	class ENGINE_API InputSystem
	{
	public:
		static bool Init();
		static bool IsKeyPressed(EngineKeys key);
		static bool IsKeyReleased(EngineKeys key);
		static bool IsKeyHeld(EngineKeys key);

		static void ProcessEvents();

	#ifdef EG_DEBUG
		static EngineKeys GetPressedKey() { return EngineKeys::LeftClick; };
	#endif

	private:
		static std::unique_ptr<InputManager> s_InputManager;
	};
}