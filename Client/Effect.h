#pragma once
#include "myGameObject.h"
#include "myTransform.h"
#include "myAnimator.h"
#include "myImage.h"
#include "myResourceManager.h"

namespace my
{
	class Effect : public GameObject
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
	};
}

