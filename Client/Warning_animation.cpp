#include "warning_animation.h"
#include "myObject.h"
#include "Krochi.h"

namespace my
{
	Warning_animation::Warning_animation()
	{

	}

	void Warning_animation::Initialize()
	{
		warning_Effect = ResourceManager::Load<Image>(L"warning_Effect", L"..\\Resources\\warning.bmp");

		EffectAnimator = AddComponent<Animator>();
		EffectAnimator->CreateAnimation(L"warning_Effect", warning_Effect, Vector2::Zero, 12, 1, 12, 0.045f, 255, 0, 255);

		EffectPos = GetComponent<Transform>();
		EffectPos->setScale(2.4f, 2.4f);

		EffectAnimator->Play_NO_RE(L"warning_Effect", false);
	}
	void Warning_animation::Update()
	{
		EffectPos = GetComponent<Transform>();
		EffectPos->setPos(Krochi::getPlayerPos() + Vector2(3, -115));

		if (EffectAnimator->IsComplete())
		{
			object::Destory(this);
		}

		GameObject::Update();
	}
	void Warning_animation::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}