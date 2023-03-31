#pragma once
#include "Enemy.h"

namespace my
{
	class Effect : public Enemy
	{
	public:
		Effect();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		Transform* EffectPos;
		Animator* EffectAnimator;
		Image* Damaged_Effect;

		friend class Enemy;
		friend class White_Fly;
	};
}

