#pragma once

#include "Renderer/Core/Renderer.h"
#include "Renderer/Architecture/Shader.h"
#include "Renderer/Architecture/Buffer.h"
#include "Renderer/Architecture/ArrayObject.h"
#include "Renderer/Architecture/Camera/PerspectiveCamera.h"

namespace Engine::Renderer
{
	class SceneRenderer : public Renderer
	{
	public:
		SceneRenderer();
		~SceneRenderer();
		
		void Setup(); //temp function to manage when the renderer calls all the opengl stuff
		virtual void Render();

	private:
		//Shader* m_TestShader;
		VertexBuffer m_VertexBuffer;
		IndexBuffer m_IndexBuffer;
		ArrayObject m_ArrayObject;
		PerspectiveCamera m_Camera;


		unsigned int m_Vao = 0;
	
		

		std::vector<float> m_VertData = {
			 0.5f,  0.5f,  0.f,
			 0.5f, -0.5f,  0.f,
			-0.5f, -0.5f,  0.f,
			-0.5f,  0.5f,  0.f
		};

		std::vector<unsigned int> m_IndexData = {
			0, 1, 3,
			1, 2, 3
		};

	};

}
