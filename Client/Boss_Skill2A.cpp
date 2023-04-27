#include "Boss_Skill2A.h"
#include "Boss_Skill2.h"
#include "Effect2.h"

namespace my
{
	Boss_Skill2A::Boss_Skill2A()
	{
		this->setName(L"Ice_a");
	}

	void Boss_Skill2A::Initialize()
	{
		Ice = ResourceManager::Load<Image>(L"ice_a", L"..\\Resources\\Boss_pattern_a.bmp");

		Ice_Animation = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		Ice_Animation->CreateAnimation(L"ice_a", Ice, Vector2::Zero, 1, 1, 1, 0.1f, 255, 0, 255);
		Ice_Animation->Play(L"ice_a", false);

		Ice_Tr = GetComponent<Transform>();
		Ice_Tr->setScale(2.0f, 2.0f);

		Ice_Pos = Ice_Tr->getPos();

		if (Ice_Pos.x > Krochi::getPlayerPos().x)
			R = true;
		else
			R = false;

		GameObject::Initialize();
	}
	void Boss_Skill2A::Update()
	{
		mTime += Time::getDeltaTime();

		if (mTime < 0.4f)
			Ice_Pos = skill->getSkillPos();
		else if (mTime < 0.65)
		{
			if (R)
				Ice_Pos += Vector2(-1500 * Time::getDeltaTime(), 1500 * Time::getDeltaTime());
			else
				Ice_Pos += Vector2(1500 * Time::getDeltaTime(), -1500 * Time::getDeltaTime());;
		}
		if (mTime > 0.65)
			object::Destory(this);

		Ice_Tr->setPos(Ice_Pos);

		GameObject::Update();
	}

	void Boss_Skill2A::Render(HDC hdc)
	{
		Ice_Tr->setPos(Ice_Pos);
		GameObject::Render(hdc);
	}
}
