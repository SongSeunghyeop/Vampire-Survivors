#include "Lightning.h"

namespace my
{
	Lightning::Lightning()
	{
		this->setName(L"Lightning");
	}

	void Lightning::Initialize()
	{
		Skill_Image = ResourceManager::Load<Image>(L"Light", L"..\\Resources\\Lightning4.bmp");

		Skill_Animator = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		Skill_Animator->CreateAnimation(L"Light", Skill_Image, Vector2::Zero, 5, 1, 5, 0.05f, 255, 0, 255);
		Skill_Animator->Play(L"Light", false);
		Skill_Animator->GetCompleteEvent(L"Light") = std::bind(&Lightning::skill_CompleteEvent, this);
		
		Skil_Tr = GetComponent<Transform>();
		Skil_Tr->setScale(Vector2(2.5f, 1.4f));

		Skill_Collider = AddComponent<Collider>();
		Skill_Collider->setCenter(Vector2(-17, 164));
		Skill_Collider->setSize(Vector2(58, 58));
		Skill_Collider->setRGB(0, 255, 0);

		GameObject::Initialize();
	}
	void Lightning::Update()
	{
		GameObject::Update();
	}

	void Lightning::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Skil_Tr->getPos());

		GameObject::Render(hdc);
	}

	void Lightning::skill_CompleteEvent()
	{
		object::Destory(this);
	}
}
