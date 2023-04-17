#pragma once
#include "Enemy.h"

namespace my
{
	class Effect;
	class Level_Item;
	class Boss_After;

	class Boss : public GameObject
	{
		enum class eBossState
		{
			Death,
			Move,
			Back_Move,
			Attack,
		};

	public:
		Boss();
		~Boss();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void move();
		void death();
		void back_move();
		void attack();

		virtual void onCollisionEnter(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionStay(class Collider* other) override;
		
	static Vector2 getBossPos() { return movePos; }

	private:
		static Vector2 movePos;

		Animator* BossAnimator;
		Collider* BossCollider;
		Transform* Boss_TR;
		Vector2 Ppos;

		Boss* otherEnemy;
		Effect* mEffect;
		//
		Image* Boss_R;
		Image* Boss_L;
		Image* bDamaged_R;
		Image* bDamaged_L;
		Image* Boss_Die_R;
		Image* Boss_Die_L;
		//
		int boss_hp;
		float delay = 0.0f;
		float skill_Time = 0.0f;
		float Boss_vel;
		eBossState eState;

		friend class Boss_After;
	};
}

