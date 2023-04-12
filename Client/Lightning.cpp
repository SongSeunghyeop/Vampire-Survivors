#include "Lightning.h"

namespace my
{
	Lightning::Lightning()
	{
		this->setName(L"Lightning");
	}

	void Lightning::Initialize()
	{
		lightning = ResourceManager::Load<Image>(L"Light", L"..\\Resources\\Lightning4.bmp");


		lightning_Animation = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		lightning_Animation->CreateAnimation(L"Light", lightning, Vector2::Zero, 5, 1, 5, 0.045f, 255, 0, 255);
		lightning_Animation->Play(L"Light", false);
		lightning_Animation->GetCompleteEvent(L"Light") = std::bind(&Lightning::skill_CompleteEvent, this);
		
		lightning_Tr = GetComponent<Transform>();
		lightning_Tr->setScale(Vector2(2.5f, 1.4f));

		lightning_Collider = AddComponent<Collider>();
		lightning_Collider->setCenter(Vector2(-17, 164));
		lightning_Collider->setSize(Vector2(58, 58));
		lightning_Collider->setRGB(0, 255, 0);

	}
	void Lightning::Update()
	{
		GameObject::Update();
	}

	void Lightning::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(lightning_Tr->getPos());

		GameObject::Render(hdc);
	}

	void Lightning::skill_CompleteEvent()
	{
		object::Destory(this);
	}
}
