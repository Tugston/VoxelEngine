/*
* File: Buffer.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-26-03 (yyyy/mm/dd)
*
* Description: Basic wrapper around all OpenGL buffers the engine requires as needed 
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//STND
#include <vector>
#include <limits>

//ENGINE
#include "Core/Core.h"

namespace Engine::Renderer
{

	//currently working on this, but just pushing this since I have the editor updated
	class BaseBuffer
	{	
	protected:
		BaseBuffer() = default;
		~BaseBuffer() = default;

		virtual void Create() = 0;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void Release() = 0;

		UINT32 m_ID = (std::numeric_limits<UINT32>::max)();
	};

	class VertexBuffer : public BaseBuffer
	{
	public:
		VertexBuffer() = default;
		~VertexBuffer();

		VertexBuffer(VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&) = delete;

		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;

		virtual void Create() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;
		
		void BufferData(std::vector<float>& data, unsigned int drawType) const;

	private:
		virtual void Release() override;
	};
	
	//Index buffer requires a VAO to be bound
	class IndexBuffer : public BaseBuffer
	{
	public:
		IndexBuffer() = default;
		~IndexBuffer();

		IndexBuffer(IndexBuffer&) = delete;
		IndexBuffer& operator=(IndexBuffer&) = delete;

		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;

		virtual void Create() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;

		void BufferData(std::vector<unsigned int>& data, unsigned int drawType) const;

	private:
		virtual void Release() override;
	};

	class FrameBuffer : public BaseBuffer
	{
	public:
		FrameBuffer() = default;
		~FrameBuffer();

		FrameBuffer(const FrameBuffer&) = delete;
		FrameBuffer& operator=(const FrameBuffer&) = delete;

		FrameBuffer(FrameBuffer&& other) noexcept;
		FrameBuffer& operator=(FrameBuffer&& other) noexcept;

		virtual void Create() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;

		void BufferTexture2D(unsigned int target, unsigned int attachment, unsigned int source, int mipMap) const;

	private:
		virtual void Release() override;
	};

}
