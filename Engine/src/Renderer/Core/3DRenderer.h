#pragma once

#include "Renderer/Core/Renderer.h"

namespace Engine::Renderer
{
	class ENGINE_API Renderer3D : public Renderer
	{
	public:
		Renderer3D();
		~Renderer3D();
		
		void Setup(); //temp function to manage when the renderer calls all the opengl stuff
		virtual void Render();

	private:
		unsigned int m_VertShader = 0;
		unsigned int m_FragShader = 0;
		unsigned int m_ShaderProgram = 0;

		unsigned int m_Vao = 0;
		unsigned int m_Vbo = 0;
		unsigned int m_Ebo = 0;

		float m_VertData[12] = {
			 0.5f,  0.5f,  0.f,
			 0.5f, -0.5f,  0.f,
			-0.5f, -0.5f,  0.f,
			-0.5f,  0.5f,  0.f
		};

		int m_IndexData[6] = {
			0, 1, 3,
			1, 2, 3
		};

	};

}
