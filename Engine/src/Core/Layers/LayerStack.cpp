#include "LayerStack.h"

namespace Engine
{
	std::vector<Layer*> LayerStack::m_Layers = {};
	unsigned int LayerStack::m_emplaceIdex = 0;

	//maybe init needs something in the future, just temporarily returning true
	bool LayerStack::Init()
	{
		return true;
	}

	void LayerStack::Destroy()
	{
		for (int i = 0; i < m_Layers.size(); i++)
		{
			delete m_Layers[i];
		}

		m_Layers.clear();
	}

	void LayerStack::PushSpaceLayer(Layer* layer)
	{
		m_Layers.emplace(CurrentLocation(), layer);
		layer->Attach();
		m_emplaceIdex++;
	}

	void LayerStack::PushUILayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->Attach();
	}

	void LayerStack::RemoveLayer(const std::vector<Layer*>::iterator& LayerPosition)
	{
		//grab the index for the layer
		std::size_t index = std::distance(std::begin(m_Layers), LayerPosition);
		
		delete *LayerPosition;
		m_Layers.erase(LayerPosition);

		//if the layer is a world layer, reduce the emplace index
		if(index < m_emplaceIdex)
			m_emplaceIdex--;
	}

	std::vector<Layer*>::iterator LayerStack::Top()
	{
		std::vector<Layer*>::iterator it = m_Layers.begin();
		return it;
	}

	std::vector<Layer*>::iterator LayerStack::Bottom()
	{
		std::vector<Layer*>::iterator it = m_Layers.end();
		return it;
	}

	std::vector<Layer*>::iterator LayerStack::CurrentLocation()
	{
		std::vector<Layer*>::iterator it = m_Layers.begin() + m_emplaceIdex;
		return it;
	}
}
