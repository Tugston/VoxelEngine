#pragma once

//STND
#include <string>

//VENDOR
#include "VENDOR/IMGUI/imgui.h"
#include "VENDOR/IMGUI/imgui_impl_glfw.h"
#include "VENDOR/IMGUI/imgui_impl_opengl3.h"

namespace Engine
{
	class DebugUI
	{
	public:

		enum class ElementType
		{
			Text = 0
		};

		static bool Init();
		static void Destroy();

		static void BeginUI(const std::string& name);
		static void EndUI();

		static void Refresh();

		static void Render();


		template<typename t>
		static inline void AddElement(ElementType type, t value)
		{
			switch (type)
			{
			case ElementType::Text:
				ImGui::Text(value);
				break;
			default:
				break;
			}
		}

	};
}

