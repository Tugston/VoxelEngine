#pragma once

//just some common things I feel each renderer would need, so making a base class

#include "Core/Core.h"

namespace Engine::Renderer
{
	class ENGINE_API Renderer
	{
	public:
		virtual ~Renderer() = default;
	protected:
		Renderer() {};
	public:
		virtual void Render() = 0;
		virtual void SetID(unsigned char id) { m_RendererID = id; };
		virtual unsigned char GetID() { return m_RendererID; };
	private:
		unsigned char m_RendererID = -1;
	};
}
