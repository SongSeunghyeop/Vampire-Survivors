#pragma once
#include "myScene.h"

namespace my 
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();
		static void Destroy();
		static void LoadScene(eSceneType type);
		static Scene* getActiveScene() { return activeScene; }

	private:
		static std::vector<Scene*> mScenes;
		static Scene* activeScene; 
	};
}

