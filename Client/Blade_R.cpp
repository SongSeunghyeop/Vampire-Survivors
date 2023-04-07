#include "Blade_R.h"

namespace my
{
	Blade_R::Blade_R()
	{
		this->setName(L"Skill");
	}

	void Blade_R::Initialize()
	{
		Skill_R = ResourceManager::Load<Image>(L"Skill_R", L"..\\Resources\\Blade_All_Red.bmp");

		Blade_Tr = GetComponent<Transform>();
		Blade_Tr->setScale(Vector2(1.7, 3.5f));

		Blade_Collider = AddComponent<Collider>();
		Blade_Collider->setCenter(Vector2(-48, -26));
		Blade_Collider->setSize(Vector2(220, 64));
		Blade_Collider->setRGB(0, 255, 0);
		
		Blade_Animator = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		Blade_Animator->CreateAnimation(L"Attack_R", Skill_R, Vector2::Zero, 4, 1, 4, 0.05f, 255, 0, 255);
		Blade_Animator->Play(L"Attack_R", false);
		Blade_Animator->GetCompleteEvent(L"Attack_R") = std::bind(&Blade_R::skillR_CompleteEvent, this);

	}
	void Blade_R::Update()
	{
		//Blade_Tr->setPos(Krochi::getPlayerPos() + Vector2(34.0f, -35.0f));
		GameObject::Update();
	}

	void Blade_R::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Blade_Tr->getPos());

		GameObject::Render(hdc);
	}

	void Blade_R::skillR_CompleteEvent()
	{
		object::Destory(this);
	}
}
