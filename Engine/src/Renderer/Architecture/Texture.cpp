#include "egpch.h"
#include "Texture.h"

//ENGINE
#include "Renderer/Core/RenderCore.h"

//VNDR
#include <stb/stb_image.h>

namespace Engine::Renderer
{
	//************
	//Base Texture
	//************
	Texture::Texture()
	{
		GL_CHECK(glGenTextures(1, &m_id));
		Bind();
	}

	Texture::~Texture()
	{
		GL_CHECK(glDeleteTextures(1, &m_id));
	}

	//************
	//Base Texture
	//************
	 
	
	//**********
	//TEXTURE 2D
	//**********

	Texture2D::Texture2D(std::string_view fileName)
	{
		//defaults for most cases
		SetWrap(GL_REPEAT, GL_REPEAT);
		SetFilter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
		int width, height, nrChannels = 0;
		unsigned char* textureData = stbi_load(fileName.data(), &width, &height, &nrChannels, 0);

		if (textureData)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			LOG_WARN("<Texture.cpp> Texture 2D data failed to load");
		}
		
		stbi_image_free(textureData);
	}

	void Texture2D::Bind() const
	{
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_id));
	}

	void Texture2D::UnBind() const
	{
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Texture2D::SetFilter(unsigned int minFilter, unsigned int magFilter) const
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	}

	void Texture2D::SetWrap(unsigned int wrapS, unsigned int wrapT) const
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	}

	//**********
	//TEXTURE 2D
	//**********

	

}
