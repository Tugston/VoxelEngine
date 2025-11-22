#pragma once

//EDTR
#include "BaseSlot.h"


namespace Editor
{
	class Vector2FSlot : public BaseSlot
	{
	public:
		Vector2FSlot(std::string_view label, float* xRef, float* yRef): BaseSlot(label, xRef), m_YRef(yRef) {};
		~Vector2FSlot() {};

		virtual void Draw() const override {
			ImGui::Text(m_Label.data());
			ImGui::SameLine();

			ImGui::PushItemWidth(70);
			ImGui::DragFloat("##x", static_cast<float*>(m_ValRef), DRAG_SPEED, std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			ImGui::SameLine();
			ImGui::DragFloat("##y", static_cast<float*>(m_YRef), DRAG_SPEED, std::numeric_limits<float>::min(), std::numeric_limits<float>::max());

			ImGui::PopItemWidth();
		}

	private:
		float* m_YRef = nullptr;
	};

	class Vector2DSlot : public BaseSlot
	{
	public:
		Vector2DSlot(std::string_view label, double* xRef, double* yRef) : BaseSlot(label, xRef), m_YRef(yRef) {};
		~Vector2DSlot() {};

		virtual void Draw() const override {	
			ImGui::Text(m_Label.data());
			ImGui::SameLine();

			ImGui::PushItemWidth(70);
			ImGui::DragScalar("##x", ImGuiDataType_Double, static_cast<double*>(m_ValRef), DRAG_SPEED, std::numeric_limits<double*>::min(), std::numeric_limits<double*>::max());
			ImGui::SameLine();
			ImGui::DragScalar("##y", ImGuiDataType_Double, static_cast<double*>(m_YRef), DRAG_SPEED, std::numeric_limits<double*>::min(), std::numeric_limits<double*>::max());

			ImGui::PopItemWidth();
		}

	private:
		double* m_YRef = nullptr;
	};
}
