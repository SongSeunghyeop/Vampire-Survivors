#include "Boss_Skill2_1.h"
#include "Effect2.h"

namespace my
{
	Boss_Skill2_1::Boss_Skill2_1()
	{
		this->setName(L"Ice");
	}

	void Boss_Skill2_1::Initialize()
	{
		Ice = ResourceManager::Load<Image>(L"ice2", L"..\\Resources\\Boss_pattern2.bmp");

		Ice_Animation = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		Ice_Animation->CreateAnimation(L"ice2", Ice, Vector2::Zero, 1, 1, 1, 0.1f, 255, 0, 255);
		Ice_Animation->Play(L"ice2", false);

		Ice_Tr = GetComponent<Transform>();
		Ice_Tr->setScale(1.5f, 1.5f);

		Ice_Pos = Ice_Tr->getPos();

		if (Ice_Pos.x > Krochi::getPlayerPos().x)
		{
			R = true;

			Ice_Collider = AddComponent<Collider>();
			Ice_Collider->setCenter(Vector2(-39, -77));
			Ice_Collider->setSize(Vector2(45, 45));
			Ice_Collider->setRGB(0, 255, 0);
		}
		else
		{
			R = false;

			Ice_Collider = AddComponent<Collider>();
			Ice_Collider->setCenter(Vector2(25, -13));
			Ice_Collider->setSize(Vector2(45, 45));
			Ice_Collider->setRGB(0, 255, 0);
		}

		GameObject::Initialize();
	}
	void Boss_Skill2_1::Update()
	{
		mTime += Time::getDeltaTime();

		if (mTime < 0.15f)
		{
			if (R)
				Ice_Pos += Vector2(500 * Time::getDeltaTime(), 500 * Time::getDeltaTime());
			else
				Ice_Pos += Vector2(-500 * Time::getDeltaTime(), -500 * Time::getDeltaTime());
		}
		else if (mTime < 0.26f)
		{
			if (R)
				Ice_Pos += Vector2(-1900 * Time::getDeltaTime(), -1900 * Time::getDeltaTime());
			else
				Ice_Pos += Vector2(1900 * Time::getDeltaTime(), 1900 * Time::getDeltaTime());
		}

		if (mTime > 0.35f)
			object::Destory(this);

		Ice_Tr->setPos(Ice_Pos);

		GameObject::Update();
	}

	void Boss_Skill2_1::Render(HDC hdc)
	{
		Ice_Tr->setPos(Ice_Pos);
		GameObject::Render(hdc);
	}
}
