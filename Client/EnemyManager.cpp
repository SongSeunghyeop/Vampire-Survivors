#include "EnemyManager.h"
#include "LevelManager.h"

namespace my
{
	EnemyManager::EnemyManager()
	{
		Enemy_Time = 0.0f;
	}
	EnemyManager::~EnemyManager()
	{

	}

	void EnemyManager::Initialize()
	{
		Enemy_Create();
		Enemy_Create();

		GameObject::Initialize();
	}
	void EnemyManager::Update()
	{
		if (LevelManager::Level_Up)
		{
			
		}
		if (!LevelManager::Level_Up && !LevelManager::Show_on)
		{
			Enemy_Time += Time::getDeltaTime();
		}

		if (Enemy_Time >= 10.0f)
		{
			Enemy_Create();
			Enemy_Time = 0.0f;
		}

		GameObject::Update();
	}
	void EnemyManager::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void EnemyManager::Release()
	{
		GameObject::Release();
	}
	void EnemyManager::Enemy_Create()
	{
		for (int i = 0; i < 12; i++) 
		{
			RandPos.x = rand() % 1440 - 720;  // -720 ~ 720
			RandPos.y = rand() % 880 - 440; //  -440 ~ 440

			while ((RandPos.x > -650 && RandPos.x < 650) && // 650 
				(RandPos.y > -370 && RandPos.y < 370)) //370
			{
				RandPos.x = rand() % 1440 - 720;
				RandPos.y = rand() % 880 - 440;
			}

			enemy = object::Instantiate<Enemy>(Krochi::getPlayerPos() + RandPos, eLayerType::ENEMY);
			enemy->Init_Pos = RandPos;
		}
	}
}