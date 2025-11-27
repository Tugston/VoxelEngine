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
		BaseBuffer(UINT32 amnt) {};
		~BaseBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		UINT32 m_ID = (std::numeric_limits<unsigned int>::max)();
	};

	class VertexBuffer : public BaseBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		//assignment override is used for assigning ecs meshes to the renderer object meshes
		VertexBuffer& operator=(const VertexBuffer& other) noexcept {
			if (this == &other) return *this;
			m_ID = other.m_ID;
			return *this;
		};

		virtual void Bind() const override;
		virtual void UnBind() const override;
		
		void BufferData(std::vector<float>& data, unsigned int drawType) const;
	};
	
	//Index buffer requires a VAO to be bound
	class IndexBuffer : public BaseBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		//assignment override is used for assigning ecs meshes to the renderer object meshes
		IndexBuffer& operator=(const IndexBuffer& other) noexcept {
			if (this == &other) return *this;
			m_ID = other.m_ID;
			return *this;
		};

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void BufferData(std::vector<unsigned int>& data, unsigned int drawType) const;
	};

	class FrameBuffer : public BaseBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		//assignment override is used for assigning ecs meshes to the renderer object meshes
		FrameBuffer& operator=(const FrameBuffer& other) noexcept {
			if (this == &other) return *this;
			m_ID = other.m_ID;
			return *this;
		};

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void BufferTexture2D(unsigned int target, unsigned int attachment, unsigned int source, int mipMap) const;
	};

}
