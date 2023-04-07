#include "Blade_L.h"

namespace my
{
	Blade_L::Blade_L()
	{
		this->setName(L"Blade");
	}

	void Blade_L::Initialize()
	{
		Skill_L = ResourceManager::Load<Image>(L"Skill_L", L"..\\Resources\\Blade_All5_Red.bmp");

		Blade_Tr = GetComponent<Transform>();
		Blade_Tr->setScale(Vector2(1.7f, 3.5f)); // 1.7 / 3.5

		Blade_Collider = AddComponent<Collider>();
		Blade_Collider->setCenter(Vector2(-69, -3));
		Blade_Collider->setSize(Vector2(220, 64));
		Blade_Collider->setRGB(0, 255, 0);

		Blade_Animator = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		Blade_Animator->CreateAnimation(L"Attack_L", Skill_L, Vector2::Zero, 4, 1, 4, 0.05f, 255, 0, 255);
		Blade_Animator->GetCompleteEvent(L"Attack_L") = std::bind(&Blade_L::skillL_CompleteEvent, this);
		Blade_Animator->Play(L"Attack_L", false);
	}
	void Blade_L::Update()
	{
		//Blade_Tr->setPos(Krochi::getPlayerPos() + Vector2(-110.0f, -35.0f));
		GameObject::Update();
	}

	void Blade_L::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Blade_Tr->getPos());

		GameObject::Render(hdc);
	}

	void Blade_L::skillL_CompleteEvent()
	{

		object::Destory(this);
	}
}
