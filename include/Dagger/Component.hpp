#ifndef DAGGER_COMPONENT_HPP
#define DAGGER_COMPONENT_HPP

namespace Dagger
{
	class Entity;

	class Component
	{
	private:
		bool isActive = true;
		bool isAlive = true;
	public:
		Entity* entity = nullptr;
		virtual void Init() {}
		virtual void Update() {}
		virtual void Draw() {}
		void Activate() { isActive = true; }
		void Deactivate() { isActive = false; }
		virtual ~Component() {}
	};
}
#endif