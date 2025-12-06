/*
* File: ArrayObject.cpp
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
#include "ArrayObject.h"

//ENGINE
#include "Renderer/Core/RenderCore.h"

#include <memory>

namespace Engine::Renderer
{
	//another converter that handles what type the attrib actually is
	static GLenum ShaderDataTypeConversion(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:		return GL_BOOL;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:		return GL_FLOAT;
		}
	}

	static unsigned int SizeCountConversion(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:		return 1;
		case ShaderDataType::Int:		return 1;
		case ShaderDataType::Int2:		return 2;
		case ShaderDataType::Int3:		return 3;
		case ShaderDataType::Int4:		return 4;
		case ShaderDataType::Float:		return 1;
		case ShaderDataType::Float2:	return 2;
		case ShaderDataType::Float3:	return 3;
		case ShaderDataType::Float4:	return 4;
		case ShaderDataType::Mat3:		return 3;
		case ShaderDataType::Mat4:		return 4;
		}
	}

	ArrayObject::~ArrayObject()
	{
		Release();
	}

	ArrayObject::ArrayObject(ArrayObject&& other) noexcept
	{
		m_ID = other.m_ID;
		other.m_ID = (std::numeric_limits<UINT32>::max)();
	}

	ArrayObject& ArrayObject::operator=(ArrayObject&& other) noexcept
	{
		if (this == &other) return *this;
		Release();
		m_ID = other.m_ID;
		other.m_ID = (std::numeric_limits<UINT32>::max)();
	}

	void ArrayObject::Create()
	{
		GL_CHECK(glGenVertexArrays(1, &m_ID));
	}

	void ArrayObject::Bind() const
	{
		GL_CHECK(glBindVertexArray(m_ID));
	}

	void ArrayObject::UnBind() const
	{
		GL_CHECK(glBindVertexArray(0));
	}

	void ArrayObject::SetAttribData(const unsigned int idx, const AttribData& data, const VertexBuffer& vertBuffer, const IndexBuffer& indexBuffer)
	{
		Bind();
		vertBuffer.Bind();
		//indexBuffer.Bind();
		
		GL_CHECK(glVertexAttribPointer(idx, SizeCountConversion(data.type), ShaderDataTypeConversion(data.type), data.normalized,
			data.stride, (void*)data.offset));

		GL_CHECK(glEnableVertexAttribArray(idx));
	}

	void ArrayObject::Release()
	{
		if (m_ID != (std::numeric_limits<UINT32>::max)())
		{
			GL_CHECK(glDeleteVertexArrays(1, &m_ID));
			m_ID = (std::numeric_limits<UINT32>::max)();
		}
	}
}
