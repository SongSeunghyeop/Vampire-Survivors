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
		EffectAnimator->CreateAnimation(L"warning_Effect", warning_Effect, Vector2::Zero, 7, 1, 7, 0.08f, 255, 0, 255);

		EffectPos = GetComponent<Transform>();
		EffectPos->setScale(2.2f, 2.2f);

		EffectAnimator->Play_NO_RE(L"warning_Effect", false);
	}
	void Warning_animation::Update()
	{
		EffectPos = GetComponent<Transform>();
		EffectPos->setPos(Krochi::getPlayerPos() + Vector2(3, -110));

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