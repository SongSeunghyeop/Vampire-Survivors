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
			Slow,
		};
		enum class eEnemyType
		{
			BLACK,
			ZOMBIE,
			SKULL,
			CANDLE,
		};


	public:
		Enemy();
		~Enemy();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void move();
		void death();
		void back_move();
		void slow();
		void none() {};

		virtual void onCollisionEnter(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionStay(class Collider* other) override;
		
		Transform* getEnemyPos() { return Enemy_TR; }
	private:
		eEnemyState eState;

		Animator* EnemyAnimator;
		Collider* EnemyCollider;

		Transform* Enemy_TR;
		Vector2 movePos;
		Vector2 prevPos;
		Vector2 Ppos;

		Enemy *otherEnemy;
		Effect* mEffect;
		Effect2* mEffect2;
		Level_Item* lv_Item;


		eEnemyType eType;
		//
		Image* EnemyR_Img;
		Image* EnemyL_Img;
		Image* Damaged_R;
		Image* Damaged_L;
		Image* Die_R;
		Image* Die_L;
		//
		Image* Zombie_R;
		Image * Zombie_L;
		Image* zDamaged_R;
		Image* zDamaged_L;
		Image * Zombie_Die_R;
		Image * Zombie_Die_L;
		//
		Image* Skull_R;
		Image* Skull_L;
		Image* sDamaged_R;
		Image* sDamaged_L;
		Image* Skull_Die_R;
		Image* Skull_Die_L;
		//

		Image* candle;
		int monster_hp;
		float Distance;
		float delay = 0.0f;
		static bool Finded;
		float Enemy_vel;
		float vel_type1;
		float vel_type2;
		float vel_type3;

		Vector2 Init_Pos;

		friend class EnemyManager;
	};
}

