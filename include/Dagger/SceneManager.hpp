#ifndef DAGGER_SCENEMANAGER_HPP
#define DAGGER_SCENEMANAGER_HPP

#include <vector>

#include <Dagger\Renderer.hpp>
#include <Dagger\Scene.hpp>

namespace Dagger
{
	class SceneManager
	{
	private:
		std::vector<Scene*> scenes;
	public:
		SceneManager();
		~SceneManager();

		void UpdateScene(float dt);
		void RenderScene();

		void PopScene();
		void PushScene(Scene* newScene);
	};
}
#endif