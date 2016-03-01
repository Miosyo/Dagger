#ifndef	DAGGER_ENTITY_HPP
#define DAGGER_ENTITY_HPP

#include <vector>
#include <array>
#include <bitset>

#include <Dagger\Component.hpp>

#define MAX_COMPONENTS 32

namespace Dagger
{

	using ComponentID = std::size_t;

	using ComponentBitset = std::bitset<MAX_COMPONENTS>;
	using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

	class Entity
	{
	private:
		std::vector<Component*> components;
		ComponentBitset componentBitset;
		ComponentArray componentArray;
		bool alive = true;
		bool active = true;
	public:
		Entity();
		~Entity();
		void Draw();
		void Update();
		//void SendMessage(Message MSG);

		ComponentID getUniqueComponentID() { static ComponentID lasID = 0u; return lasID++; }

		template<typename T>
		ComponentID getComponentTypeID()
		{
			static ComponentID typeID = getUniqueComponentID();
			return typeID;
		}

		template<typename T>
		Component& addComponent()
		{
			if (hasComponent<T>()) return T();

			T* c = new T();
			c->entity = this;
			components.emplace_back(c);
			componentArray[getComponentTypeID<T>()] = c;
			componentBitset[getComponentTypeID<T>()] = true;

			c->Init();

			return *c;
		}

		template<typename T>
		bool hasComponent()
		{
			return componentBitset[getComponentTypeID<T>()];
		}

		template<typename T>
		T& getComponent()
		{
			if (hasComponent<T>())
			{
				Component* ptr = componentArray[getComponentTypeID<T>()];
				return *static_cast<T*>(ptr);
			}
			return T();
		}

		bool isAlive() { return alive; }
		bool isActive() { return active; }
		void Destroy() { alive = false; }
		void Activate() { active = true; }
		void Deactivate() { active = false; }
	};
}
#endif