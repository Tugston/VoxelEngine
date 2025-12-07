/*
* File: Buffer.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-26-03 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Buffer.h"

#include "Renderer/Core/RenderCore.h"

#define COPY_ASSIGNMENT()\
if (this == &other) return *this;\
Release();\
m_ID = other.m_ID;\
other.m_ID = (std::numeric_limits<UINT32>::max)();\

namespace Engine::Renderer
{
	//*************
	//Vertex Buffer
	//*************
	VertexBuffer::~VertexBuffer()
	{
		Release();
	}

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

	void VertexBuffer::Release()
	{
		if (m_ID != (std::numeric_limits<UINT32>::max)())
		{
			GL_CHECK(glDeleteBuffers(1, &m_ID));
			m_ID = (std::numeric_limits<UINT32>::max)();
		}
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	{
		m_ID = other.m_ID;
		other.m_ID = (std::numeric_limits<UINT32>::max)();
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
	{
		COPY_ASSIGNMENT();
	}

	void VertexBuffer::Create()
	{
		GL_CHECK(glGenBuffers(1, &m_ID));
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

	IndexBuffer::~IndexBuffer()
	{
		Release();
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

	void IndexBuffer::Release()
	{
		if (m_ID != (std::numeric_limits<UINT32>::max)())
		{
			glDeleteBuffers(1, &m_ID);
			m_ID = (std::numeric_limits<UINT32>::max)();
		}
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
	{
		m_ID = other.m_ID;
		other.m_ID = (std::numeric_limits<UINT32>::max)();
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
	{
		COPY_ASSIGNMENT();
	}

	void IndexBuffer::Create()
	{
		GL_CHECK(glGenBuffers(1, &m_ID));
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

	FrameBuffer::~FrameBuffer()
	{
		Release();
	}

	FrameBuffer::FrameBuffer(FrameBuffer&& other) noexcept
	{
		m_ID = other.m_ID;
		other.m_ID = (std::numeric_limits<UINT32>::max)();
	}

	FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other) noexcept
	{
		COPY_ASSIGNMENT();
	}

	void FrameBuffer::Create()
	{
		GL_CHECK(glGenFramebuffers(1, &m_ID));
	}

	void FrameBuffer::Bind() const
	{
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
	}

	void FrameBuffer::UnBind() const
	{
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void FrameBuffer::BufferTexture2D(unsigned int attachment, unsigned int source, int mipMap) const
	{
		GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, source, mipMap));
	}

	void FrameBuffer::Release()
	{
		if (m_ID != (std::numeric_limits<UINT32>::max)())
		{
			GL_CHECK(glDeleteFramebuffers(1, &m_ID));
			m_ID = (std::numeric_limits<UINT32>::max)();
		}
	}

	//************
	//Frame Buffer
	//************


	//*************
	//Render Buffer
	//*************

	RenderBuffer::~RenderBuffer()
	{
		Release();
	}

	RenderBuffer::RenderBuffer(RenderBuffer&& other) noexcept
	{
		m_ID = other.m_ID;
		other.m_ID = (std::numeric_limits<UINT32>::max)();
	}

	RenderBuffer& RenderBuffer::operator=(RenderBuffer&& other) noexcept
	{
		COPY_ASSIGNMENT();
	}

	void RenderBuffer::Create()
	{
		GL_CHECK(glGenRenderbuffers(1, &m_ID));
	}

	void RenderBuffer::Bind() const
	{
		GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_ID));
	}

	void RenderBuffer::UnBind() const
	{
		GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0));
	}

	void RenderBuffer::RenderBufferStorage(unsigned int format, int width, int height)
	{
		GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, format, width, height));
	}

	void RenderBuffer::Release()
	{
		if (m_ID != (std::numeric_limits<UINT32>::max)())
		{
			GL_CHECK(glDeleteRenderbuffers(1, &m_ID));
			m_ID = (std::numeric_limits<UINT32>::max)();
		}
	}

}
