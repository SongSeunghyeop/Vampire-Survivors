#pragma once
#include "Enemy.h"
#include "MyGameObject.h"
#include "Krochi.h"
namespace my
{
	class EnemyManager : public GameObject
	{
		enum class eEnemyType
		{
			BLACK,
			ZOMBIE,
		};
	public:
		EnemyManager();
		~EnemyManager();

		void Enemy_Create();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		float Enemy_Time;
		Vector2 RandPos;
		int Init_Num;
		Enemy* enemy;
	};
}

