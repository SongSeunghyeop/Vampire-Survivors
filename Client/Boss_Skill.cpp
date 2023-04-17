#include "Boss_Skill.h"
#include "Effect2.h"

namespace my
{
	Boss_Skill::Boss_Skill()
	{
		this->setName(L"meteor");
	}

	void Boss_Skill::Initialize()
	{
		meteor = ResourceManager::Load<Image>(L"meteor", L"..\\Resources\\Boss_Attack.bmp");

		meteor_Animation = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		meteor_Animation->CreateAnimation(L"meteor", meteor, Vector2::Zero, 1, 1, 1, 0.1f, 255, 0, 255);
		meteor_Animation->Play(L"meteor", false);

		meteor_Tr = GetComponent<Transform>();
		meteor_Tr->setScale(Vector2(2.0f, 2.0f));

		meteor_Collider = AddComponent<Collider>();
		meteor_Collider->setCenter(Vector2(-15, -30));
		meteor_Collider->setSize(Vector2(55, 60));
		meteor_Collider->setRGB(0, 255, 0);

		GameObject::Initialize();
	}
	void Boss_Skill::Update()
	{
		mTime += Time::getDeltaTime();

		meteor_Pos = meteor_Tr->getPos();
		meteor_Pos.y += Time::getDeltaTime() * 640.0f;
		meteor_Tr->setPos(meteor_Pos);

		GameObject::Update();
	}

	void Boss_Skill::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(meteor_Tr->getPos());

		if (meteor_Tr->getPos().y > Krochi::getPlayerPos().y + 30)
		{
			object::Instantiate<Effect2>(meteor_Tr->getPos(), eLayerType::EFFECT);
			object::Destory(this);
		}

		GameObject::Render(hdc);
	}
}
