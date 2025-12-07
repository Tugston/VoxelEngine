/*
* File: Texture.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-22 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Texture.h"

//ENGINE
#include "Renderer/Core/RenderCore.h"

//VNDR

namespace Engine::Utility
{
	//************
	//Base Texture
	//************
	Texture::Texture()
	{
	}

	Texture::~Texture()
	{
		GL_CHECK(glDeleteTextures(1, &m_Id));
	}

	//************
	//Base Texture
	//************
	 
	
	//**********
	//TEXTURE 2D
	//**********

	Texture2D::~Texture2D()
	{
	}

	void Texture2D::Create(std::string_view fileName)
	{
		GL_CHECK(glGenTextures(1, &m_Id));
		Bind();

		//defaults for most cases
		SetWrap(GL_REPEAT, GL_REPEAT);
		SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

		int width, height, nrChannels = 0;
		unsigned char* textureData = stbi_load(fileName.data(), &width, &height, &nrChannels, 0);

		if (textureData)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
			GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
		}
		else
		{
			LOG_WARN("<Texture.cpp> Texture 2D data failed to load");
		}

		stbi_image_free(textureData);
	}

	void Texture2D::CreateEmpty(TextureDefaultParams params)
	{
		GL_CHECK(glGenTextures(1, &m_Id));
		Bind();

		SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
		SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, params.width, params.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}

	void Texture2D::Bind() const
	{
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_Id));
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
