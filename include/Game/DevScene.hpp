#ifndef GAME_DEVSCENE_HPP
#define GAME_DEVSCENE_HPP

#include <Dagger\Scene.hpp>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Game
{
	class DevScene : public Dagger::Scene
	{
	public:
		// Inherited via Scene
		virtual void Init() override;
		virtual void Destroy() override;
		virtual void OnUpdate(float dt) override;
		virtual void OnRender() override;
	};
}
#endif