#include "Boss_Skill2.h"
#include "Effect2.h"

namespace my
{
	Boss_Skill2::Boss_Skill2()
	{
		this->setName(L"Ice");
	}

	void Boss_Skill2::Initialize()
	{
		Ice = ResourceManager::Load<Image>(L"ice", L"..\\Resources\\Boss_pattern.bmp");

		Ice_Animation = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		Ice_Animation->CreateAnimation(L"ice", Ice, Vector2::Zero, 1, 1, 1, 0.1f, 255, 0, 255);
		Ice_Animation->Play(L"ice", false);

		Ice_Tr = GetComponent<Transform>();
		Ice_Tr->setScale(1.5f, 1.5f);

		Ice_Pos = Ice_Tr->getPos();

		Ice_Collider = AddComponent<Collider>();
		Ice_Collider->setCenter(Vector2(25, -79));
		Ice_Collider->setSize(Vector2(45, 45));
		Ice_Collider->setRGB(0, 255, 0);

		GameObject::Initialize();
	}
	void Boss_Skill2::Update()
	{
		mTime += Time::getDeltaTime();
		
		 if (mTime < 0.26f)
		{
				Ice_Pos += Vector2(1900 * Time::getDeltaTime(), -1900 * Time::getDeltaTime());
		}

		if (mTime > 0.35f)
			object::Destory(this);

		Ice_Tr->setPos(Ice_Pos);

		GameObject::Update();
	}

	void Boss_Skill2::Render(HDC hdc)
	{
		Ice_Tr->setPos(Ice_Pos);
		GameObject::Render(hdc);
	}
}
