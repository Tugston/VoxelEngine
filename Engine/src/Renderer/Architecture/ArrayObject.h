/*
* File: ArrayObject.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-26-03 (yyyy/mm/dd)
*
* Description: Basic wrapper around OpenGL array objects
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGINE
#include "Core/Core.h"
#include "Renderer/Architecture/Buffer.h"

//STND
#include <memory>
#include <cstdint>


namespace Engine::Renderer
{
	//data types for the attrib pointer
	enum class ShaderDataType
	{
		Bool = 0,
		Int,
		Int2,
		Int3,
		Int4,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4
	};

	//since some ShaderDataTypes have the same size (ie Int, Float)
	//have to make a helper function for parsing the size, because they cannot be stored directly in the enum
	static uint32_t ParseShaderDataType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:		return sizeof(bool);
		case ShaderDataType::Int:		return sizeof(int);
		case ShaderDataType::Int2:		return sizeof(int) * 2;
		case ShaderDataType::Int3:		return sizeof(int) * 3;
		case ShaderDataType::Int4:		return sizeof(int) * 4;
		case ShaderDataType::Float:		return sizeof(float);
		case ShaderDataType::Float2:	return sizeof(float) * 2;
		case ShaderDataType::Float3:	return sizeof(float) * 3;
		case ShaderDataType::Float4:	return sizeof(float) * 4;
		case ShaderDataType::Mat3:		return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4:		return sizeof(float) * 4 * 4;
		}

	};

	struct AttribData
	{
	public:
		ShaderDataType type;
		int32_t size = 0;
		bool normalized = false;
		UINT32 stride = 0;
		unsigned int offset = 0;

		AttribData() = default;
		AttribData(ShaderDataType type, bool normalized = false, unsigned int offset = 0) :
			type(type), size(ParseShaderDataType(type)), normalized(normalized), offset(offset)
		{}
	};

	class ArrayObject
	{
	public:
		ArrayObject() = default;
		~ArrayObject();

		ArrayObject(ArrayObject&) = delete;
		ArrayObject& operator=(ArrayObject&) = delete;

		ArrayObject(ArrayObject&& other) noexcept;
		ArrayObject& operator=(ArrayObject&& other) noexcept;


		void Create();
		void Bind() const;
		void UnBind() const;

		void SetAttribData(const unsigned int index, const AttribData& data, const VertexBuffer& vertBuffer, const IndexBuffer& indexBuffer);

	private:
		void Release();

		UINT32 m_ID = (std::numeric_limits<UINT32>::max)();
	};

}
