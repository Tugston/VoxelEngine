#pragma once

#include "./Core/Core.h"
#include "./Components/Positionals/Transform.h"

//ecs uses the hash lookup for components, I could add a compile ids for each component and then look up their index in a vector for o(1), but I dont know how to implement that
//and this map works good enough, I am not trying to make unreal engine. I am aware there are better ways though. Better ways for this whole engine matter of fact!

namespace Engine::Scene::ECS
{
	using EntityID = UINT32;

	class Registry
	{
	public:
		Registry();
		~Registry();

		EntityID CreateEntity()
		{
			EntityID currentId = m_NextEntityID;
			m_NextEntityID++;
			return currentId;
		};

		void DeleteEntity(EntityID entityID)
		{
			for (auto& [typeID, pool] : m_Components)
				pool->RemoveComponent(entityID);
		}

		template<typename t, typename... Args>
		void AddComponent(EntityID entityID, Args&&... args)
		{
			ComponentPool<t>* pool = GetPool<t>();
		
			if (pool->HasComponent(entityID))
			{
				LOG_WARN("Component already exists on entity, returning component");
				return pool->GetComponent(entityID);
			}
			
			return pool->Add(entityID, t(std::forward<Args>(args)...));
		}
		
		template<typename t>
		void RemoveComponent(EntityID entityID) 
		{
			ComponentPool<t>* pool = GetPool<t>();

			if (pool->HasComponent(entityID))
				pool->RemoveComponent(entityID);
			else
				LOG_WARN("Entity did not contain component, removed nothing");
		}
	
	protected:

		class InheritPool {
			virtual ~InheritPool() = default;
		};

		//sparse set implementation that I think works
		template<typename t>
		class ComponentPool : InheritPool
		{
		public:
			ComponentPool()
			{
				denseEntities.resize(5, 0);
				denseComponents.resize(5);
				sparse.resize(5, 0);
			}

			~ComponentPool()
			{
				denseComponents.clear();
				denseEntities.clear();
				sparse.clear();
			}

			//the component data for each instance of the pool is the same 
			//the type name is for all the pools for the different components (transform components, render components, movement component, etc)
			//so the type name is just so the entitie's component values can be stored properly

			//returns the component back
			t& Add(EntityID entityID, const t& componentData)
			{
				if (sparse.size() <= entityID)
					sparse.resize(entityID + 1, 0);

				sparse[entityID] = m_DenseComponents.size();
				denseComponents.push_back(componentData);
				denseEntities.push_back(entityID);

				return denseComponents.back();
			}

			void RemoveComponent(EntityID entityID)
			{
				//not going to log anything, because destroying an entity needs to call this
				//so it would be weird and misleading logs
				if (id >= sparse.size)
					return;

				int i = sparse[entityID];
				sparse[entityID] = 0;

				denseComponents.erase(denseComponents.begin() + i);
			};

			template<typename t>
			bool HasComponent(EntityID id)
			{
				if (id >= sparse.size)
					return false;

				return typeid(denseComponents[sparse[id]]) == typeid(t);
			}

			template<typename t>
			t* GetComponent(EntityID id)
			{
				if (id >= sparse.size)
					return nullptr;

				int i = sparse[entity];

				if (i < denseEntities.size() && denseEntities[i] == id)
					return &denseComponents[i];

				//not found
				return nullptr;
			}

			std::vector<EntityID> denseEntities;
			std::vector<t> denseComponents;
			std::vector<int> sparse;
		};

	private:
		//this the culptrit I was ranting about at the top
		template<typename t>
		ComponentPool<t>& GetPool() const
		{
			type_info poolID = typeid(t);
			ComponentPool<t> foundPool;
			if (!m_Components.contains(poolID))
				foundPool = m_Components.emplace(poolID, std::make_unique<ComponentPool<t>>);
			else
				foundPool = m_Components.find(poolID);

			return foundPool;
		}
	
	private:
		std::unordered_map<type_info, std::unique_ptr<ComponentPool<InheritPool>>> m_Components;
		EntityID m_NextEntityID = 1;
	};
}
