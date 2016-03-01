#include <Dagger\Entity.hpp>

namespace Dagger
{
	Entity::Entity()
	{
		components = std::vector<Component*>();
	}

	Entity::~Entity()
	{

	}

	void Entity::Draw()
	{
		for (Component *c : components) c->Draw();
	}

	void Entity::Update()
	{
		for (Component *c : components) c->Update();
	}
}