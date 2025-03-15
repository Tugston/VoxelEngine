#pragma once

#include "Renderer/Core/Renderer.h"

namespace Engine::Renderer
{
	class ENGINE_API Renderer3D : public Renderer
	{
	public:
		Renderer3D();
		~Renderer3D();

		virtual void Render();

	private:
		unsigned int m_Vao;
		unsigned int m_Vbo;
		unsigned int m_Ebo;

		float m_VertData[12] = {
			 0.5f,  0.5f,  0.f,
			 0.5f, -0.5f,  0.f,
			-0.5f, -0.5f,  0.f,
			-0.5f,  0.5f,  0.f
		};

		int m_IndexData[6] = {
			0, 1, 2,
			3, 2, 1
		};

	};

}
