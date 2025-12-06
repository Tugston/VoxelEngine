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
		Clear();
		Logger::LogMessage(Logger::LogType::Warning, "Layer Stack Destroyed!");
	}

	void LayerStack::PushWorldLayer(Layer* layer)
	{
		m_Layers.emplace(CurrentLocation(), layer);
		layer->Attach();
		m_emplaceIdex++;
		Logger::LogMessage(Logger::LogType::Message, "World Layer Added (Total of: {} Layers)", m_Layers.size());
	}

	void LayerStack::PushUILayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->Attach();
		Logger::LogMessage(Logger::LogType::Message, "UI Layer Added (Total of: {} Layers)", m_Layers.size());
	}

	void LayerStack::Clear()
	{
		if (m_Layers.size() == 0)
			return;

		for (auto i : m_Layers)
		{
			delete i;
		}

		m_Layers.clear();
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

	const bool LayerStack::CheckLayerExists(unsigned char id)
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
		Logger::LogMessage(Logger::LogType::Critical, "LAYER NOT FOUND! Ignore if it was intended to not be found.");
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
		std::vector<Layer*>::iterator it = m_Layers.begin() + m_emplaceIdex;
		return it;
	}
}
