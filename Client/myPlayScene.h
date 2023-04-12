#pragma once
#include "myScene.h"
#include "myCollisionManager.h"
#include "myCamera.h"
#include "myScene.h"
#include "mySceneManager.h"
#include "myInput.h"

#include "Krochi.h"
#include "EnemyManager.h"
#include "Field.h"
#include "PlayerManager.h"
#include "Treasure.h"

namespace my
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();

	private:
		Krochi* krochi;
		Field* field;
		EnemyManager* E_manager;
		PlayerManager* levelmanager;
		Treasure* treasure;
	};
}