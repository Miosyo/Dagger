#include <Dagger\SceneManager.hpp>

namespace Dagger
{
	SceneManager::SceneManager()
	{

	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::UpdateScene(float dt)
	{
		if (scenes.back() != NULL)
		{
			scenes.back()->OnUpdate(dt);
		}
	}

	void SceneManager::RenderScene(Renderer& renderer)
	{
		if (scenes.back() != NULL)
		{
			scenes.back()->OnRender(renderer);
		}
	}

	void SceneManager::PopScene()
	{
		if (scenes.back() != NULL)
		{
			scenes.back()->Destroy();
			delete scenes.back();
			scenes.pop_back();
		}
	}

	void SceneManager::PushScene(Scene* newScene)
	{
		scenes.push_back(newScene);
		scenes.back()->Init();
	}
}