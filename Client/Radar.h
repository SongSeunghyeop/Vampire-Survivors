#pragma once
#include "Krochi.h"
#include "Enemy.h"
#include "Boss.h"

namespace my
{
	class Radar: public Krochi
	{
	public:
		Radar();
		~Radar();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void onCollisionStay(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionEnter(class Collider* other) override;
		
		void myErase(Collider *c)
		{
			std::vector<Collider*>::iterator it;

			for (it = Enemies.begin(); it != Enemies.end(); it++)
			{
				if (*it == c)
				{
					Enemies.erase(it);
					break;
				}
			}
		}
		static Vector2 getRandomEnemyPos(int a);
		static int getEnemyNum();
	private:
		Collider* radar_Collider;
		Transform* rader_Tr;
		Vector2 Radar_Size;
	
		static std::vector<Collider*> Enemies;
		static Vector2* enemyPos;
		friend class Krochi;
	};
}

