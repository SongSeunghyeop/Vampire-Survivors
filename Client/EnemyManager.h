#pragma once
#include "Enemy.h"
#include "Boss.h"

namespace my
{
	class EnemyManager : public GameObject
	{
	public:
		EnemyManager();
		~EnemyManager();

		void Enemy_Create();
		void Dragon_Create();
		void Dragon_Active();
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		static bool Boss_on;
		static float boss_Time;

		void setR(int r) { R = r; }

	private:
		float Enemy_Time;
		Vector2 RandPos;
		int Init_Num;
		Enemy* enemy;
		Enemy* dragon;
		std::vector<Enemy*> dragons;
		Boss* boss;

		Vector2 dir;
		Vector2 rotation;
		Vector2 dragon_Pos;

		bool dragon_init;
		float distance;
		float R;
		float mTime = 0.0f;
	};
}

