#pragma once

//EDTR
#include "BaseSlot.h"


namespace Editor
{
	class FloatSlot : public BaseSlot
	{
	public:
		FloatSlot(std::string_view label, float* ref): BaseSlot(label, ref) {};
		~FloatSlot() {};

		virtual void Draw() const override {
			ImGui::DragFloat(m_Label.data(), static_cast<float*>(m_ValRef), DRAG_SPEED, std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
		};
	};
}
