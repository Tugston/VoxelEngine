#pragma once

//just some common things I feel each renderer would need, so making a base class

#include "Core/Core.h"

namespace Engine::Renderer
{	
	class Renderer
	{
	public:
		enum class RenderTarget: UINT8
		{
			Window,
			FrameBufferTexture
		};

		virtual ~Renderer() = default;
	protected:
		Renderer();
	public:
		virtual void Render(RenderTarget target) = 0;
		virtual void SetID(unsigned char id) { m_RendererID = id; };
		virtual unsigned char GetID() { return m_RendererID; };
	private:
		unsigned char m_RendererID = -1;
	};
}
