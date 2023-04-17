#include "Effect.h"
#include "myObject.h"

namespace my
{
	Effect::Effect()
	{

	}

	void Effect::Initialize()
	{
		Damaged_Effect = ResourceManager::Load<Image>(L"Effect", L"..\\Resources\\effect_All.bmp");

		EffectAnimator = AddComponent<Animator>();
		EffectAnimator->CreateAnimation(L"Damaged_Effect", Damaged_Effect, Vector2::Zero, 3, 1, 3, 0.03f, 255, 0, 255);
  
		EffectPos = GetComponent<Transform>();
		EffectPos->setScale(2.2f, 2.2f);

		EffectAnimator->Play(L"Damaged_Effect", false);
	}
	void Effect::Update()
	{
		EffectPos = GetComponent<Transform>();
		
		if (EffectAnimator->IsComplete())
		{
			object::Destory(this);
		}

		GameObject::Update();
	}
	void Effect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}