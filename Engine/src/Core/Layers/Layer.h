#pragma once

//ENGINE
#include "Core/Core.h"
#include "Renderer/Core/RenderData.h"

namespace Engine
{
	class Layer
	{
	protected:
		Layer() {};
		Layer(unsigned char id) : m_ID(id) {};
	public:
		virtual ~Layer() = default;

		virtual void Attach() = 0;
		virtual void Detach() = 0;
		virtual void GetDrawData() = 0;
		virtual void InputEvent() = 0;

		inline unsigned char GetID() const { return m_ID; };

	protected:
		//there will only be a few layers
		//this can be stored in a byte obviously
		unsigned char m_ID = 0;
	};
}
