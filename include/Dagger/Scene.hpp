#ifndef DAGGER_SCENE_HPP
#define	DAGGER_SCENE_HPP

#include <Dagger\Renderer.hpp>
#include <Dagger\ResourceManager.hpp>

namespace Dagger
{
	class Scene
	{
	protected:
		Renderer* renderer = nullptr;
	public:
		virtual void Init() = 0;
		virtual void Destroy() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender() = 0;
	};
}
#endif