#pragma once

//EDTR
#include "BaseSlot.h"


namespace Editor
{
	class DoubleSlot : public BaseSlot
	{
	public:
		DoubleSlot(std::string_view label, double* ref) : BaseSlot(label, ref) {};
		~DoubleSlot() {};

		virtual void Draw() const override {
			ImGui::DragScalar(m_Label.data(), ImGuiDataType_Double, static_cast<double*>(m_ValRef), DRAG_SPEED, std::numeric_limits<double*>::min(), std::numeric_limits<double*>::max());
		};
	};
}
