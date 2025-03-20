#pragma once

//ENGINE
#include "Core/Core.h"

namespace Engine
{
	class ENGINE_API Layer
	{
	protected:
		Layer() {};
		Layer(unsigned char id) : m_ID(id) {};
	public:
		virtual ~Layer() = default;

		virtual void Attach() = 0;
		virtual void Detach() = 0;
		virtual void Draw() = 0;
		virtual void InputEvent() = 0;

		inline unsigned char GetID() const { return m_ID; };

	protected:
		//there will only be a few layers
		//this can be stored in a byte obviously
		unsigned char m_ID = 0;
	};
}
