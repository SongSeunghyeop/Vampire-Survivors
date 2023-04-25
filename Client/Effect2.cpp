#include "Effect2.h"
#include "myObject.h"

namespace my
{
	Effect2::Effect2()
	{

	}

	void Effect2::Initialize()
	{
		Damaged_Effect = ResourceManager::Load<Image>(L"Effect2", L"..\\Resources\\Player_Effect.bmp");

		EffectAnimator = AddComponent<Animator>();
		EffectAnimator->CreateAnimation(L"Damaged_Effect", Damaged_Effect, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);

		EffectPos = GetComponent<Transform>();
		EffectPos->setScale(3.5f, 3.5f);

		EffectAnimator->Play_NO_RE(L"Damaged_Effect", false);
	}
	void Effect2::Update()
	{
		EffectPos = GetComponent<Transform>();

		if (EffectAnimator->IsComplete())
		{
			object::Destory(this);
		}

		GameObject::Update();
	}
	void Effect2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}