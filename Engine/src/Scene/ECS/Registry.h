#pragma once

//STND
#include <typeindex>

//ENGINE
#include "./Core/Core.h"
#include "./Components/Positionals/Transform.h"
#include "./Core/Logger.h"

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
			return m_NextEntityID++;
		};

		void DeleteEntity(EntityID entityID)
		{
			for (auto& [typeID, pool] : m_Components)
				pool->RemoveComponent(entityID);
		}

		template<typename t, typename... Args>
		t* AddComponent(EntityID entityID, Args&&... args)
		{
			ComponentPool<t>* pool = GetPool<t>();
		
			if (pool->HasComponent<t>(entityID))
			{
				LOG_WARN("<Registry.h> Component already exists on entity [ {} ], returning component", entityID);
				return pool->GetComponent<t>(entityID);
			}
			
			return pool->Add(entityID, t(std::forward<Args>(args)...));
		}
		
		template<typename t>
		void RemoveComponent(EntityID entityID) 
		{
			ComponentPool<t>* pool = GetPool<t>();

			if (pool->HasComponent<t>(entityID))
				pool->RemoveComponent(entityID);
			else
				LOG_MSG("<Registry.h> Entity [ {} ] does not contain component, removed nothing", entityID);
		}

		template<typename t>
		const t* GetComponent(EntityID entityID)
		{
			ComponentPool<t>* pool = GetPool<t>();

			if (pool->HasComponent<t>(entityID))
				return pool->GetComponent<t>(entityID);
			else
				LOG_MSG("<Registry.h> Component does not exist on entity [ {} ]", entityID);
		}
	
	protected:

		class InheritPool {
		public:
			virtual ~InheritPool() = default;

			//need to add this as the inherit so it can be accessed without the cast
			virtual void RemoveComponent(EntityID entityID) = 0;
		};

		//sparse set implementation that I think works
		template<typename t>
		class ComponentPool : public InheritPool
		{
		public:
			ComponentPool()
			{
				sparse.resize(5, UINT32_MAX);
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
			//the existing check is done in the registry itself, felt it was slightly better to do it there
			t* Add(EntityID entityID, const t& componentData)
			{
				if (sparse.size() <= entityID)
					sparse.resize(entityID + 1, 0);

				denseComponents.push_back(componentData);
				denseEntities.push_back(entityID);
				sparse[entityID] = denseComponents.size() - 1;

				return &denseComponents.back();
			}

			virtual void RemoveComponent(EntityID entityID) override
			{
				//not going to log anything, because destroying an entity needs to call this
				//so it would be weird and misleading logs
				if (entityID >= sparse.size())
					return;

				const int i = sparse[entityID];
				sparse[entityID] = UINT32_MAX;

				//the off by one is accounted for when adding
				denseComponents.erase(denseComponents.begin() + i);
				denseEntities.erase(denseEntities.begin() + i);
			};

			template<typename t>
			bool HasComponent(EntityID id) const
			{
				if (id >= sparse.size())
					return false;

				return sparse[id] != UINT32_MAX;
			}

			//I rly want this to be reference, but I dont rly want exceptions
			//especially for direct game api stuff (this ultimately gets called from GameObjects)
			template<typename t>
			t* GetComponent(EntityID id)
			{
				if (id >= sparse.size())
					return nullptr;

				const int i = sparse[id];

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
		ComponentPool<t>* GetPool()
		{
			std::type_index poolID(typeid(t));
			auto foundPoolIt = m_Components.find(poolID);

			//a component that is active is obviously trying to be found
			//so if the pool doesn't exist for the component type then best to just make it
			if (foundPoolIt == m_Components.end())
			{
				std::unique_ptr<ComponentPool<t>> pool = std::make_unique<ComponentPool<t>>();
				ComponentPool<t>* poolPtr = pool.get();
				m_Components.emplace(poolID, std::move(pool));
				return poolPtr;
			}

			return static_cast<ComponentPool<t>*>(foundPoolIt->second.get());
		}
	
	private:
		//InheritPool type is for a default component type
		std::unordered_map<std::type_index, std::unique_ptr<InheritPool>> m_Components;
		EntityID m_NextEntityID = 0;
	};
}
