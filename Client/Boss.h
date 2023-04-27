#pragma once
#include "Enemy.h"

namespace my
{
	class Boss_After;
	class Boss_Hp;

	class Boss : public GameObject
	{
		enum class eBossState
		{
			Move,
			Back_Move,
			Attack,
			Idle,
			None,
		};

	public:
		Boss();
		~Boss();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void move();
		void back_move();
		void attack_1();
		void attack_2();

		virtual void onCollisionEnter(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionStay(class Collider* other) override;
		
	static Vector2 getBossPos() { return movePos; }
	float getBoss_hp() { return boss_hp; }
	protected:
	private:
		static Vector2 movePos;

		float boss_hp;

		Animator* boss_Animator;
		Collider* boss_Collider;
		Transform* boss_Tr;
		Vector2 Ppos;

		Boss* otherEnemy;
		Effect* mEffect;
		//
		Image* Boss_R;
		Image* Boss_L;
		Image* bDamaged_R;
		Image* bDamaged_L;
		//
		float delay = 0.0f;
		float skill_Time = 0.0f;
		float Boss_vel;
		eBossState eState;
		
		Boss_Hp* hp;

		friend class Boss_After;
	};
}

