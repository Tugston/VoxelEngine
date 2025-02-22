#pragma once

//ENGINE
#include "KeyDefines.h"
#include "Core/Core.h"
#include "Core/Logger.h"

//STND
#include <memory>
#include <map>

namespace Engine
{

	class ENGINE_API InputSystem
	{
	public:
		static bool Init();
		static bool KeyPressed(EngineKeys key);
		static bool KeyReleased(EngineKeys key);
	};
}