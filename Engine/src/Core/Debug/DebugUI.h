#pragma once

//ENGINE
#include "Core/Debug/ElementType.h"
#include "Core/Logger.h"

//STND
#include <string>
#include <tuple>

//VENDOR
#include "VENDOR/IMGUI/imgui.h"
#include "VENDOR/IMGUI/imgui_impl_glfw.h"
#include "VENDOR/IMGUI/imgui_impl_opengl3.h"

namespace Engine::Debug
{
	class UI
	{
	public:

		static bool Init();
		static void Destroy();

		static void BeginUI(const std::string& name);
		static void EndUI();

		static void Refresh();

		static void Render();

		//type is the type of element to be added (see imgui api)
		//displayValue is  what is shows as is (ie text shows displayValue)
		//modifyValue is what needs to be changed (ie transforms, in the order of imgui, besides display and modify value)
		template<typename t, typename v, typename... Args>
		static inline void AddElement(ElementType type, const t& displayValue, v* modifyvalue, Args&&... args)
		{
			//compile time check
			constexpr auto argCheck = [](size_t x) constexpr
				{
					return sizeof...(args) >= x;
				};
			
			switch (type)
			{
			case ElementType::Text:
			{
				//NO ADDITIONAL ARGUMENTS NEEDED
				if constexpr (argCheck(0))
				{
					if constexpr (std::is_convertible_v<t, char>)
					{
						ImGui::Text(displayValue);
					}
					else if constexpr (std::is_convertible_v<t, std::string>)
					{
						ImGui::Text(static_cast<std::string>(displayValue).c_str());
					}
				}
				break;
				
			}
			case ElementType::ColoredText:
			{				
				//upack the color arg
				if constexpr (argCheck(1))
				{
					unsigned int hexColor = std::get<0>(std::forward_as_tuple(std::forward<Args>(args)...));

					auto calculateColor = [=](unsigned int position)
						{
							return (unsigned char)(hexColor >> (position * 8) & 0xFF);
						};

					std::function<unsigned char(int)> getColorByte = calculateColor;
					
					unsigned char R = getColorByte(1);
					unsigned char G = getColorByte(2);
					unsigned char B = getColorByte(3);
					unsigned char A = getColorByte(4);
					ImVec4 convertedColor(B, G, R, A); //weird imgui order?

					if constexpr (std::is_convertible_v<t, char>)
					{
						ImGui::TextColored(convertedColor, displayValue);
					}
					else if constexpr (std::is_convertible_v<t, std::string>)
					{
						ImGui::TextColored(convertedColor, static_cast<std::string>(displayValue).c_str());
					}
				}
				break;
			}
			case ElementType::CheckBox:
			{
				//NO ADDITIONAL ARGUMENTS NEEDED
				if (argCheck(0))
				{

					if constexpr (std::is_convertible_v<t, char> && std::is_convertible_v<v*, bool*>)
					{
						ImGui::Checkbox(displayValue, modifyvalue);
					}
					else if constexpr (std::is_convertible_v<t, std::string> && std::is_convertible_v<v*, bool*>)
					{
						ImGui::Checkbox(static_cast<std::string>(displayValue).c_str(), modifyvalue);
					}
				}
				break;
			}
			case ElementType::DragFloat:
			{
				//unpack the args
				if constexpr (argCheck(5))
				{
					float v_speed = std::get<0>(std::forward_as_tuple(std::forward<Args>(args)...));
					float v_min = std::get<1>(std::forward_as_tuple(std::forward<Args>(args)...));
					float v_max = std::get<2>(std::forward_as_tuple(std::forward<Args>(args)...));
					const char* format = std::get<3>(std::forward_as_tuple(std::forward<Args>(args)...));
					ImGuiSliderFlags flags = std::get<4>(std::forward_as_tuple(std::forward<Args>(args)...));

					if constexpr (std::is_convertible_v<t, char> && std::is_convertible_v<v*, float*>)
					{
						ImGui::DragFloat(displayValue, modifyvalue, v_speed, v_min, v_max, format, flags);
					}
					else if constexpr (std::is_convertible_v<t, std::string> && std::is_convertible_v<v*, float*>)
					{
						ImGui::DragFloat(static_cast<std::string>(displayValue).c_str(), modifyvalue, v_speed, v_min, v_max, format, flags);
					}
				}
				break;
			}
			case ElementType::DragInt:
			{
				//unpack the args
				if constexpr (argCheck(5))
				{
					float v_speed = std::get<0>(std::forward_as_tuple(std::forward<Args>(args)...));
					float v_min = std::get<1>(std::forward_as_tuple(std::forward<Args>(args)...));
					float v_max = std::get<2>(std::forward_as_tuple(std::forward<Args>(args)...));
					const char* format = std::get<3>(std::forward_as_tuple(std::forward<Args>(args)...));
					int flags = std::get<4>(std::forward_as_tuple(std::forward<Args>(args)...));

					if constexpr (std::is_convertible_v<t, char> && std::is_convertible_v<v*, int*>)
					{
						ImGui::DragInt(displayValue, modifyvalue, v_speed, v_min, v_max, &format, flags);
					}
					else if constexpr (std::is_convertible_v<t, std::string> && std::is_convertible_v<v*, int*>)
					{
						ImGui::DragInt(static_cast<std::string>(displayValue).c_str(), modifyvalue, v_speed, v_min, v_max, &format, flags);
					}
				}
				break;
			}
			case ElementType::InputFloat:
			{
				//unpack args
				if constexpr (argCheck(4))
				{
					float step = std::get<0>(std::forward_as_tuple(std::forward<Args>(args)...));
					float step_fast = std::get<1>(std::forward_as_tuple(std::forward<Args>(args)...));
					const char format = (char)(std::get<2>(std::forward_as_tuple(std::forward<Args>(args)...)));
					ImGuiInputTextFlags flags = (ImGuiInputTextFlags)(std::get<3>(std::forward_as_tuple(std::forward<Args>(args)...)));

					if constexpr (std::is_convertible_v<t, char> && std::is_convertible_v<v*, float*>)
					{
						ImGui::InputFloat(displayValue, modifyvalue, step, step_fast, &format, flags);
					}
					else if constexpr (std::is_convertible_v<t, std::string> && std::is_convertible_v<v*, float*>)
					{
						ImGui::InputFloat(static_cast<std::string>(displayValue).c_str(), modifyvalue, step, step_fast, &format, flags);
					}
				}
				break;
			}
			case ElementType::InputInt:
			{
				//unpack args
				if constexpr (argCheck(3))
				{
					float step = std::get<0>(std::forward_as_tuple(std::forward<Args>(args)...));
					float step_fast = std::get<1>(std::forward_as_tuple(std::forward<Args>(args)...));
					const char format = (char)(std::get<2>(std::forward_as_tuple(std::forward<Args>(args)...)));
					ImGuiInputTextFlags flags = (ImGuiInputTextFlags)(std::get<3>(std::forward_as_tuple(std::forward<Args>(args)...)));

					if constexpr (std::is_convertible_v<t, char> && std::is_convertible_v<v*, int*>)
					{
						ImGui::InputFloat(displayValue, modifyvalue, step, step_fast, &format, flags);
					}
					else if constexpr (std::is_convertible_v<t, std::string> && std::is_convertible_v<v*, int*>)
					{
						ImGui::InputFloat(static_cast<std::string>(displayValue).c_str(), modifyvalue, step, step_fast, &format, flags);
					}
				}
				break;
			}
			default:
				Logger::LogMessage(Logger::LogType::Warning, "Debuui.h - switch, Unkown imgui element type");
				break;
			}

		}

	};
}

