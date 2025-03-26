#pragma once

#include <vector>

namespace Engine::Renderer
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(unsigned char amnt);
		~VertexBuffer();

		void BufferData(std::vector<float>& data, unsigned int drawType);
		void Bind() const;
		void UnBind() const;

	private:
		uint32_t m_ID = 0;
		unsigned char m_BufferAmnt = 1; //buffer amount is the amount of buffers, there will always be 1
	};
	
	//Index buffer requires a VAO to be bound
	class IndexBuffer
	{
	public:
		IndexBuffer();
		IndexBuffer(unsigned char amnt);
		~IndexBuffer();

		void BufferData(std::vector<unsigned int>& data, unsigned int drawType);
		void Bind() const;
		void UnBind() const;

	private:
		uint32_t m_ID = 0;
		uint32_t m_Size = 0; //size is the amount of items index'ed
		unsigned char m_BufferAmnt = 1; //buffer amount is the amount of buffers, there will always be 1
	};

}
