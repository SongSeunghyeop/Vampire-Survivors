#pragma once
#include "MyGameObject.h"
#include "myAnimator.h"
#include "myTransform.h"
#include "myImage.h" 
#include "Krochi.h"
#include "myCollider.h"

namespace my
{
	class Effect;
	class Level_Item;

	class Enemy : public GameObject
	{
		enum class eEnemyState
		{
			Death,
			None,
			Move,
			Back_Move,
		};
		enum class eEnemyType
		{
			BLACK,
			ZOMBIE,
		};


	public:
		Enemy();
		~Enemy();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void Move();
		void Back_Move();
		void Death();
		void None() {};

		//virtual void onCollisionEnter(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionStay(class Collider* other) override;
		
		Transform* getEnemyPos() { return EnemyPos; }

	private:
		eEnemyState eState;

		Animator* EnemyAnimator;
		Collider* EnemyCollider;

		Transform* EnemyPos;
		Vector2 movePos;
		Vector2 Ppos;

		Enemy *otherEnemy;
		Effect* mEffect;
		Level_Item* lv_Item;


		eEnemyType eType;
		Image* EnemyR_Img;
		Image* EnemyL_Img;
		Image* Damaged_R;
		Image* Damaged_L;
		Image* Die_R;
		Image* Die_L;

		Image* Zombie_R;
		Image * Zombie_L;
		Image * Zombie_Die_R;
		Image * Zombie_Die_L;

		int monster_hp;
		float Distance;
		float delay = 0.0f;
		static bool Finded;
		float Enemy_vel;
		Vector2 Init_Pos;

		friend class EnemyManager;
	};
}

