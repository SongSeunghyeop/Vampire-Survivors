#pragma once
#include "Effect.h"

namespace my
{
	class Warning_animation : public GameObject
	{
	public:
		Warning_animation();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		Transform* EffectPos;
		Animator* EffectAnimator;
		Image* warning_Effect;

		friend class Enemy;
	};
}

