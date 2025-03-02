#pragma once

#include "Core/Core.h"

namespace Engine
{
	class ENGINE_API Layer
	{
	public:
		Layer() {};
		virtual ~Layer() = default;

		virtual void Attach() = 0;
		virtual void Detach() = 0;
		virtual void Draw() = 0;
		virtual void InputEvent() = 0;
	};
}
