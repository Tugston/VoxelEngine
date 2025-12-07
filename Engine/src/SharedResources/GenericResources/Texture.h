/*
* File: Texture.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-22 (yyyy/mm/dd)
*
* Description: wrapper class around opengl texture calls and id
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once


//ENGINE
#include "Core/Core.h"

#include <stb/stb_image.h>

namespace Engine::Utility
{
	//these values were sourced from the gl constants data sheet
	//raw.githubusercontent.com/KhronosGroup/OpenGL-Registry/master/xml/gl.xml?utm
	enum class TextureParamName : unsigned int
	{
		DEPTH_STENCIL_TEXTURE_MODE	= 0x90EA,
		TEXTURE_BASE_LEVEL			= 0x813c,
		TEXTURE_COMPARE_FUNC		= 0x884D,
		TEXTURE_COMPARE_MODE		= 0x884C,
		TEXTURE_LOD_BIAS			= 0x8501,
		TEXTURE_MIN_FILTER			= 0x2801,
		TEXTURE_MAG_FILTER			= 0x2800,
		TEXTURE_MIN_LOD				= 0x813A,
		TEXTURE_MAX_LOD				= 0x813B,
		TEXTURE_MAX_LEVEL			= 0x813D,
		TEXTURE_SWIZZLE_R			= 0x8E42,
		TEXTURE_SWIZZLE_G			= 0x8E43,
		TEXTURE_SWIZZLE_B			= 0x8E44,
		TEXTURE_SWIZZLE_A			= 0x8E45,
		TEXTURE_WRAP_S				= 0x2802,
		TEXTURE_WRAP_T				= 0x2803,
		TEXTURE_WRAP_R				= 0x8072,

		//Vector Commands only
		TEXTURE_BORDER_COLOR		= 0x1004,
		TEXTURE_SWIZZLE_RGBA		= 0x8E46
	};

	//empty texture will return empty file name!
	struct TextureDefaultParams
	{
		TextureDefaultParams(std::string_view fileName = "", int width = 1280, int height = 720): fileName(fileName), width(width), height(height) {}

		std::string_view fileName = "";
		int width;
		int height;
	};

	class Texture
	{
	public:
		//create is utilized to source an image for the texture and create empty is just passed params
		virtual void Create(std::string_view filename) = 0;
		virtual void CreateEmpty(TextureDefaultParams params) = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		unsigned int GetID() { return m_Id; }

		virtual ~Texture();

	protected:
		Texture();
		unsigned int m_Id = 0;
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D() = default;
		~Texture2D();

		virtual void Create(std::string_view filename) override;
		virtual void CreateEmpty(TextureDefaultParams params) override;
		virtual void Bind() const override;
		virtual void UnBind() const override;

		void SetFilter(unsigned int minFilter, unsigned int magFilter) const;
		void SetWrap(unsigned int wrapS, unsigned int wrapT) const;
	};
}
