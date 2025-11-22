#pragma once

//EDTR
#include "BaseSlot.h"


namespace Editor
{
	class IntSlot : public BaseSlot
	{
	public:
		IntSlot(std::string_view label, float* ref): BaseSlot(label, ref) {};
		~IntSlot() {};

		virtual void Draw() const override {
			ImGui::DragInt(m_Label.data(), static_cast<int*>(m_ValRef), DRAG_SPEED, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
		};
	};
}
