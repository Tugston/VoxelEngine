#pragma once

//ENGINE
#include "Core/Layer.h"

//STND
#include<vector>

//I am going for a simple setup where each scene will have the same layers
//my current idea for layers is as so
//Game -> Engine Debug Graphics -> Game UI -> Engine UI Debug
//this is really only a system for the Game's UI to be layered on top of the Game's 3d rendering
//and it will be like that in every scene, which is why I made this static

//this class should only be engine sided

namespace Engine
{
	class LayerStack
	{
	public:
		static bool Init();
		static void Destroy();

		static void PushSpaceLayer(Layer* layer);	//actual "world" layers
		static void PushUILayer(Layer* layer);		//ui layers

		static void PopLayer(Layer* layer);


		//take advantage of the layer "stack" actually being an underlying vector

		static std::vector<Layer*>::iterator Top();
		static std::vector<Layer*>::iterator Bottom();

		//current location stores the halfway point, ie, where Space and UI layers meet
		static std::vector<Layer*>::iterator CurrentLocation();
		static inline unsigned int CurrentLocationVal() { return m_emplaceIdex; };

		static const inline std::vector<Layer*> GetLayers() { return m_Layers; };
	private:
		static std::vector<Layer*> m_Layers; //Layer Stack will have full control over layers
		static unsigned int m_emplaceIdex;
	};
}
