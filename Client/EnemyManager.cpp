#include "EnemyManager.h"
#include "PlayerManager.h"
#include "myPlayScene.h"

namespace my
{
	bool EnemyManager::Boss_on;

	EnemyManager::EnemyManager()
	{
		Enemy_Time = 0.0f;
		Init_Num = 10;
	}
	EnemyManager::~EnemyManager()
	{

	}

	void EnemyManager::Initialize()
	{
		Enemy_Create();
	
		GameObject::Initialize();
	}
	void EnemyManager::Update()
	{
		if (!PlayerManager::Level_Up && !PlayerManager::Show_on && !Boss_on)
		{
			Enemy_Time += Time::getDeltaTime();
		}

		if (Enemy_Time >= 10.0f)
		{
			Enemy_Create();

			Init_Num+= 4;
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
		for (int i = 0; i < Init_Num; i++)
		{
			RandPos.x = rand() % 1440 - 720;  // -720 ~ 720
			RandPos.y = rand() % 880 - 440; //  -440 ~ 440

			while ((RandPos.x > -650 && RandPos.x < 650) && // 650 
				(RandPos.y > -370 && RandPos.y < 370)) //370
			{
				RandPos.x = rand() % 1440 - 720;
				RandPos.y = rand() % 880 - 440;
			}

			enemy = new Enemy();
			Scene* scene = SceneManager::getActiveScene();
			scene->AddGameObj(enemy, eLayerType::ENEMY);
			enemy->GameObject::GetComponent<Transform>()->setPos(Krochi::getPlayerPos() + RandPos);
			enemy->Init_Pos = RandPos;

			if(i < 30)
				enemy->eType = Enemy::eEnemyType::BLACK;
			else if(i < 60)
				enemy->eType = Enemy::eEnemyType::ZOMBIE;
			else if(i < 99)
				enemy->eType = Enemy::eEnemyType::SKULL;

			int random = rand() % 10;// 0~9;
			if(random > 1) enemy->Finded = true;

			if(i == 0 && random > 7) 
				enemy->eType = Enemy::eEnemyType::CANDLE;

			enemy->Initialize();

			if (i == 100) // 보스 출현 // i == 100이면 정확히 4분
			{
				Boss_on = true; // 몬스터 생성 중단, 모든 몬스터 사망

				boss = new Boss();
				Scene* scene = SceneManager::getActiveScene();
				scene->AddGameObj(boss, eLayerType::ENEMY);
				boss->GameObject::GetComponent<Transform>()->setPos(Krochi::getPlayerPos() + RandPos);
				boss->Initialize();
			}
		}
	}
}