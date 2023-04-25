#pragma once
#include "myResourceManager.h"
#include "MyGameObject.h"
#include "myAnimator.h"
#include "myTransform.h"
#include "Krochi.h"
#include "myImage.h" 
#include "Time.h"
#include "myCollider.h"
#include "Sound.h"
#include "Effect.h"

namespace my
{
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
			DRAGON,
			GHOST,
			CANDLE,
		};

	public:
		Enemy();

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
		
		void dskill_CompleteEvent();

	private:
		eEnemyState eState;
		eEnemyType eType;

		Animator* EnemyAnimator;
		Collider* EnemyCollider;

		Transform* Enemy_TR;
		Vector2 movePos;
		Vector2 prevPos;
		Vector2 Ppos;

		Enemy *otherEnemy;
		Effect* mEffect;
		Level_Item* lv_Item;
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
		Image* Dragon_R;
		Image* Dragon_L;
		Image* dAttack_R;
		Image* dAttack_L;
		Image* dDamaged_R;
		Image* dDamaged_L;
		//
		Image* Ghost_R;
		Image* Ghost_L;
		Image* Ghost_Run_R;
		Image* Ghost_Run_L;
		Image* gDamaged_R;
		Image* gDamaged_L;
		Image* Ghost_DieR;
		Image* Ghost_DieL;
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
		float vel_type4;
		Vector2 Init_Pos;

		Sound* damaged_Sound;

		friend class EnemyManager;
	};
}

