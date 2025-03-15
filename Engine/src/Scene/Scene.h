#pragma once

#include "Core/Core.h"

namespace Engine
{
	class ENGINE_API Scene
	{
	public:
		Scene();
		~Scene();

		void Render();

		void RemoveUI() const;

		//DEBUG ONLY
	#if defined(EG_DEBUG) || (APP_DEBUG)
		void EnableFullDebugView() const;
		void EnableDebugUI() const;
		void EnableDebugGeometry() const;
		void DisableFullDebugView() const;
		void DisableDebugUI() const;
		void DisableDebugGeometry() const;
	#endif

	private:
	};

}
