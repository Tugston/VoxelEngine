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
	public:
		//BaseBuffer(const BaseBuffer&) = delete;
		//BaseBuffer& operator=(const BaseBuffer&); <- this is dangerous for excluding, but unfortunately vectors copy 

		//I rly only allow moving
		//BaseBuffer(BaseBuffer&& other) noexcept : m_ID(other.m_ID)
		//{
			//other.m_ID = 0;
		//}

		//BaseBuffer& operator=(BaseBuffer&& other) noexcept;

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

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void BufferData(std::vector<unsigned int>& data, unsigned int drawType) const;

	private:
		UINT32 m_Size = 0; //size is the amount of items indexed
	};

	class FrameBuffer : public BaseBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void BufferTexture2D(unsigned int target, unsigned int attachment, unsigned int source, int mipMap) const;
	};

}
