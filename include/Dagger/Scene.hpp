#ifndef DAGGER_SCENE_HPP
#define	DAGGER_SCENE_HPP

#include <Dagger\Renderer.hpp>

namespace Dagger
{
	struct Scene
	{
		virtual void Init() = 0;
		virtual void Destroy() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender(Renderer& renderer) = 0;
	};
}
#endif