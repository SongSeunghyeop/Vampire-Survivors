#include "EnemyManager.h"
#include "ItemManager.h"
#include "myObject.h"

namespace my
{
	bool EnemyManager::Boss_on;
	float EnemyManager::boss_Time;

	EnemyManager::EnemyManager()
	{
		Enemy_Time = 0.0f;
		Init_Num = 8;
		boss_Time = 180.0f;
		dragon_init = false;
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
		if (!PlaySceneManager::Level_Up && !PlaySceneManager::Show_on && !Boss_on)
		{
			Enemy_Time += Time::getDeltaTime();
		}
		if (PlaySceneManager::Play_Time > boss_Time && !Boss_on) // 보스 등장, 플레이어를 제외한 모든 오브젝트 파괴
		{
			Boss_on = true;

			if (boss == NULL)
			{
				boss = object::Instantiate<Boss>
					(Krochi::getPlayerPos() + Vector2(650, -650), eLayerType::ENEMY);
			}
		}

		if (Enemy_Time >= 6.0f)
		{
			Enemy_Create();

			Init_Num += 2;
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
	void EnemyManager::Dragon_Create()
	{
		dir = Vector2(500.0f, 500.0f);
		dir.Normalize();

		for (int i = 0; i < 30; i++)
		{
			R = i * 12;

			rotation = math::Rotate(dir, R);
			dragon_Pos.x = Krochi::getPlayerPos().x + 450 * rotation.x;
			dragon_Pos.y = Krochi::getPlayerPos().y + 450 * rotation.y;

			dragon = new Enemy();
			Scene* scene = SceneManager::getActiveScene();
			scene->AddGameObj(dragon, eLayerType::ENEMY);
			dragon->GameObject::GetComponent<Transform>()->setPos(dragon_Pos);
			dragon->Init_Pos = dragon_Pos;
			dragon->eType = Enemy::eEnemyType::DRAGON;
			dragon->Initialize();
		}
		dragon_init = true;
	}
	void EnemyManager::Enemy_Create()
	{
		for (int i = 0; i < Init_Num; i++)
		{
			RandPos.x = rand() % 1800 - 900;  // -900 ~ 900
			RandPos.y = rand() % 1200 - 600; //  -600 ~ 600

			while ((RandPos.x > -700 && RandPos.x < 700) && // 700 
				(RandPos.y > -400 && RandPos.y < 400)) //400
			{
				RandPos.x = rand() % 1800 - 900;  // -900 ~ 900
				RandPos.y = rand() % 1200 - 600; //  -600 ~ 600
			}

			enemy = new Enemy();
			Scene* scene = SceneManager::getActiveScene();
			scene->AddGameObj(enemy, eLayerType::ENEMY);
			enemy->GameObject::GetComponent<Transform>()->setPos(Krochi::getPlayerPos() + RandPos);
			enemy->Init_Pos = RandPos;

			if (i < 14)
				enemy->eType = Enemy::eEnemyType::BLACK;
			else if (i < 28)
				enemy->eType = Enemy::eEnemyType::ZOMBIE;
			else if (i < 42)
				enemy->eType = Enemy::eEnemyType::SKULL;
			else
				enemy->eType = Enemy::eEnemyType::GHOST;

			enemy->Finded = true;

			int random = rand() % 10;// 0~9;

			if (i == 0 && random == 0)
				enemy->eType = Enemy::eEnemyType::CANDLE;

			enemy->Initialize();

			if (PlaySceneManager::Play_Time >= 140.0f && !dragon_init)
				Dragon_Create();
		}
	}
}