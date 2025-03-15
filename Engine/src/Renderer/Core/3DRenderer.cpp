#include "3DRenderer.h"

//just testing opengl for now, and will slowly abstract everything

#include "Renderer/Core/RenderCore.h"

Engine::Renderer::Renderer3D::Renderer3D()
{
	GL_CHECK(glewInit());
	
	GL_CHECK(glGenBuffers(1, &m_Vbo));
	GL_CHECK(glGenBuffers(1, &m_Ebo));

	GL_CHECK(glGenVertexArrays(1, &m_Vao));

	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Vbo));
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo));

	GL_CHECK(glBindVertexArray(m_Vao));
	
}

Engine::Renderer::Renderer3D::~Renderer3D()
{
}

void Engine::Renderer::Renderer3D::Render()
{
	glDrawElements(GL_STATIC_DRAW, 2, GL_TRIANGLES, &m_IndexData);
}
