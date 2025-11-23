#include "egpch.h"
#include "Buffer.h"

#include "Renderer/Core/RenderCore.h"

namespace Engine::Renderer
{
	//*************
	//Vertex Buffer
	//*************

	VertexBuffer::VertexBuffer()
	{
		GL_CHECK(glGenBuffers(1, &m_ID));
	}

	VertexBuffer::~VertexBuffer()
	{
		GL_CHECK(glDeleteBuffers(1, &m_ID));
	}
/*
	BaseBuffer& BaseBuffer::operator=(BaseBuffer&& other) noexcept
	{
		if (this == &other) return *this;
		GL_CHECK(glDeleteBuffers(1, &m_ID));
		m_ID = other.m_ID;
		other.m_ID = 0;
		return *this;
	}*/

	void VertexBuffer::BufferData(std::vector<float>& data, unsigned int drawType) const
	{
		Bind();

		switch (drawType)
		{
		case GL_STATIC_DRAW:
			GL_CHECK(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW));
			break;
		case GL_DYNAMIC_DRAW:
			GL_CHECK(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_DYNAMIC_DRAW));
			break;
		default:
			break;
		}
	}

	void VertexBuffer::Bind() const
	{
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	}

	void VertexBuffer::UnBind() const
	{
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	//*************
	//Vertex Buffer
	//*************

	//************
	//INDEX BUFFER
	//************

	IndexBuffer::IndexBuffer()
	{
		GL_CHECK(glGenBuffers(1, &m_ID));
	}

	IndexBuffer::~IndexBuffer()
	{
		GL_CHECK(glDeleteBuffers(1, &m_ID));
	}

	void IndexBuffer::BufferData(std::vector<unsigned int>& data, unsigned int drawType) const
	{
		Bind();

		switch (drawType)
		{
		case GL_STATIC_DRAW:
			GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW));
			break;
		case GL_DYNAMIC_DRAW:
			GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_DYNAMIC_DRAW));
			break;
		default:
			break;
		}
	}

	void IndexBuffer::Bind() const
	{
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	}

	void IndexBuffer::UnBind() const
	{
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}


	//************
	//Frame Buffer
	//************

	FrameBuffer::FrameBuffer()
	{
		GL_CHECK(glGenFramebuffers(1, &m_ID));
	}

	FrameBuffer::~FrameBuffer()
	{
		GL_CHECK(glDeleteFramebuffers(1, &m_ID));
	}

	void FrameBuffer::Bind() const
	{
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
	}

	void FrameBuffer::UnBind() const
	{
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void FrameBuffer::BufferTexture2D(unsigned int target, unsigned int attachment, unsigned int source, int mipMap) const
	{
		GL_CHECK(glFramebufferTexture2D(target, attachment, GL_TEXTURE_2D, source, mipMap));
	}

	//add more as needed, like Texture3D

	//************
	//Frame Buffer
	//************


}
