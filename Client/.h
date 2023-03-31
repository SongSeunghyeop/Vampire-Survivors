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

	class White_Fly : public GameObject
	{
		enum class eEnemyState
		{
			Death,
			None,
			Move,
			Stun,
			Back_Move,
		};


	public:
		White_Fly();
		~White_Fly();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void Move();
		void Back_Move();
		void Death();
		void Stun();
		void None() { };

		//virtual void onCollisionEnter(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionStay(class Collider* other) override;

		Transform* getEnemyPos() { return EnemyPos; }


	private:
		Animator* EnemyAnimator;
		Collider* EnemyCollider;

		Transform* EnemyPos;
		Vector2 movePos;
		Vector2 Ppos;

		White_Fly* otherEnemy;
		Effect* mEffect;
		Level_Item* lv_Item;

		eEnemyState eState;
		Image* EnemyR_Img;
		Image* EnemyL_Img;

		int monster_hp;
		float Distance;
		float delay = 0.0f;
		bool Damaged;
		bool Finded;

		Vector2 RandPos;
	};
}

