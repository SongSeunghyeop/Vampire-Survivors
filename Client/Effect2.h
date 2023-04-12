#pragma once
#include "Krochi.h"

namespace my
{
	class Effect2 : public GameObject
	{
	public:
		Effect2();

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

