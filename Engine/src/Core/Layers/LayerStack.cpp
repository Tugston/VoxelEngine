/*
* File: LayerStack.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-08 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/

#include "egpch.h"
#include "LayerStack.h"

#include "Core/Logger.h"

namespace Viper
{
	std::vector<Layer*> LayerStack::m_Layers = {};
	unsigned int LayerStack::m_insertIdex = 0;

	//maybe init needs something in the future, just temporarily returning true
	bool LayerStack::Init()
	{
		return true;
	}

	void LayerStack::Destroy()
	{
		Clear();
		LOG_MSG("<LayerStack.cpp> (Destroy) Layer Stack Destroyed!");
	}

	void LayerStack::PushWorldLayer(Layer* layer)
	{
		m_Layers.insert(CurrentLocation(), layer);
		layer->Attach();
		m_insertIdex++;
		LOG_MSG("<LayerStack.cpp> (PushWorldLayer) World Layer Added Successfully (Total of: {} Layers)", m_Layers.size());
	}

	void LayerStack::PushUILayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		layer->Attach();
		LOG_MSG("<LayerStack.cpp> (PushUILayer) UI Layer Added Successfully (Total of: {} Layers)", m_Layers.size());
	}

	void LayerStack::Clear()
	{
		if (m_Layers.size() == 0)
			return;

		for (auto i : m_Layers)
			delete i;

		m_Layers.clear();
	}

	void LayerStack::RemoveLayer(const std::vector<Layer*>::iterator& LayerPosition)
	{
		//grab the index for the layer
		std::size_t index = std::distance(std::begin(m_Layers), LayerPosition);
		
		delete *LayerPosition;
		m_Layers.erase(LayerPosition);

		//if the layer is a world layer, reduce the emplace index
		if(index < m_insertIdex)
			m_insertIdex--;
	}

	const bool LayerStack::CheckLayerExists(LayerID id)
	{
		//o(n), idc, there is only 4 layers
		for (auto i : m_Layers)
		{
			if (i->GetID() == id)
			{
				return true;
			}
		}
		
		//could be a serious issue in some cases if the layer with the id does not exist, but in some cases it's ok, so guess this log covers that??
		LOG_CRIT("<LayerStack.cpp> (CheckLayerExists) Layer not found! If this was intentional, please ignore.");
		return false;
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
		std::vector<Layer*>::iterator it = m_Layers.begin() + m_insertIdex;
		return it;
	}
}
