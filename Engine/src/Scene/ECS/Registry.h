#pragma once

namespace Engine::Scene::ECS
{
	class Registry
	{
	public:
		Registry();
		~Registry();

	//	void CreateEntity();

		//template<typename t>
		//void AddComponent(UINT32 entityID);
		//template<typename t>
		//void RemoveComponent(UINT32 entityID);
	
	private:
		
		//sparse set to effeciently store a few entities with a bunch of different components
		template<typename t>
		class Storage
		{
			Storage();
			~Storage();

			//the component data for each instance of Storage is the same 
			//the type name is for all the storages for the different components (transform components, render components, movement component, etc)
			//so the type name is just so the entitie's component values can be stored properly

			//returns the component back
			t& Add(UINT32 entityID, const t& componentData);

			void Remove(UINT32 entityID);

		private:
			std::vector<UINT32> m_DenseEntities;
			std::vector<t> m_DenseComponents;
			std::vector<int> m_Sparse;
		};
		
		UINT32 m_NextEntityID = 1;
	};
}
