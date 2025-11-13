#include "egpch.h"
#include "Registry.h"

namespace Engine::Scene::ECS
{
	Registry::Registry()
	{

	}

	Registry::~Registry()
	{

	}

//	void Registry::CreateEntity(UINT32 entityID)
	//{
	//}

	//void Registry::RemoveEntity(UINT32 entityID)
//	{
	//}


	// ***********************
	// STORAGE IMPLEMENTATIONS
	// ***********************

	template <typename t>
	Registry::Storage<t>::Storage()
	{
		m_DenseEntities.resize(5, 0);
		m_DenseComponents.resize(5, t);
		m_Sparse.resize(5, 0);
	}

	template <typename t>
	Registry::Storage<t>::~Storage()
	{
		m_DenseComponents.clear();
		m_DenseEntities.clear();
		m_Sparse.clear();
	}

	template<typename t>
	t& Registry::Storage<t>::Add(UINT32 entityID, const t& componentData)
	{
		if (m_Sparse.size() < entityID)
			m_Sparse.resize(entityID + 1, 0);

		m_Sparse[entityID] = m_DenseComponents.size();
		m_DenseComponents.push_back(t);
		m_DenseEntities.push_back(entityID);

		return m_DenseComponents.back();
	}

	template<typename t>
	void Registry::Storage<t>::Remove(UINT32 entityID)
	{
	}

	// ***********************
	// STORAGE IMPLEMENTATIONS
	// ***********************

}