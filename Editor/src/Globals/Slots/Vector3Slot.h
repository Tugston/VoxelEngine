#pragma once

//EDTR
#include "BaseSlot.h"


namespace Editor
{
	class Vector3FSlot : public BaseSlot
	{
	public:
		Vector3FSlot(std::string_view label, float* xRef, float* yRef, float* zRef): BaseSlot(label, xRef), m_YRef(yRef), m_ZRef(zRef) {};
		~Vector3FSlot() {};

		virtual void Draw() const override {
			ImGui::Text(m_Label.data());
			ImGui::SameLine();

			ImGui::PushItemWidth(105);
			ImGui::DragFloat("##x", static_cast<float*>(m_ValRef), DRAG_SPEED, std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			ImGui::SameLine();
			ImGui::DragFloat("##y", static_cast<float*>(m_YRef), DRAG_SPEED, std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
			ImGui::SameLine();
			ImGui::DragFloat("##z", static_cast<float*>(m_ZRef), DRAG_SPEED, std::numeric_limits<float>::min(), std::numeric_limits<float>::max());

			ImGui::PopItemWidth();
		}

	private:
		float* m_YRef = nullptr;
		float* m_ZRef = nullptr;
	};

	class Vector3DSlot : public BaseSlot
	{
	public:
		Vector3DSlot(std::string_view label, double* xRef, double* yRef, double* zRef) : BaseSlot(label, xRef), m_YRef(yRef), m_ZRef(zRef) {};
		~Vector3DSlot() {};

		virtual void Draw() const override {	
			ImGui::Text(m_Label.data());
			ImGui::SameLine();

			ImGui::PushItemWidth(105);
			ImGui::DragScalar("##x", ImGuiDataType_Double, static_cast<double*>(m_ValRef), DRAG_SPEED, std::numeric_limits<double*>::min(), std::numeric_limits<double*>::max());
			ImGui::SameLine();
			ImGui::DragScalar("##y", ImGuiDataType_Double, static_cast<double*>(m_YRef), DRAG_SPEED, std::numeric_limits<double*>::min(), std::numeric_limits<double*>::max());
			ImGui::SameLine();
			ImGui::DragScalar("##z", ImGuiDataType_Double, static_cast<double*>(m_ZRef), DRAG_SPEED, std::numeric_limits<double*>::min(), std::numeric_limits<double*>::max());

			ImGui::PopItemWidth();
		}

	private:
		double* m_YRef = nullptr;
		double* m_ZRef = nullptr;
	};
}
