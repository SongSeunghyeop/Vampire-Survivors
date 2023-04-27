#pragma once
#include "myScene.h"
#include "myCollisionManager.h"
#include "myCamera.h"
#include "myScene.h"
#include "mySceneManager.h"
#include "myInput.h"
#include "Sound.h"

#include "Krochi.h"
#include "EnemyManager.h"
#include "Field.h"
#include "ItemManager.h"
#include "PlaySceneManager.h"

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
		ItemManager* I_manager;
		PlaySceneManager* P_manager;
		Treasure* treasure;

		Sound* treasure_Sound;
		Sound* PlayScene_Sound;
		Sound* boss_bgm;
	};
}