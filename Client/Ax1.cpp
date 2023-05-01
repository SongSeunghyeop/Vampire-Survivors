#include "Ax1.h"
#include "PlaySceneManager.h"

namespace my
{
	Ax1::Ax1()
	{
		this->setName(L"Ax1");
	}
	Ax1::~Ax1()
	{

	}
	void Ax1::Initialize()
	{
		Skill_Image = ResourceManager::Load<Image>(L"AXR", L"..\\Resources\\AX1_R.bmp");
		Skill_Image2 = ResourceManager::Load<Image>(L"AXL", L"..\\Resources\\AX1_L.bmp");

		Skil_Tr = GetComponent<Transform>();
		Skil_Tr->setScale(3.2, 3.2);
		Skill_Pos = Skil_Tr->getPos();

		Skill_Collider = AddComponent<Collider>();
		Skill_Collider->setCenter(Vector2(-8, -15));
		Skill_Collider->setSize(Vector2(52, 52));
		Skill_Collider->setRGB(0, 0, 255);

		Skill_Animator = AddComponent<Animator>();
		Skill_Animator->CreateAnimation(L"axR", Skill_Image, Vector2::Zero, 8, 1, 8, 0.1f, 255,0,255);
		Skill_Animator->CreateAnimation(L"axL", Skill_Image2, Vector2::Zero, 8, 1, 8, 0.1f, 255, 0, 255);

		int r = rand() % 10;

		if(r > 4)
			Skill_Animator->Play(L"axR", true);
		else
			Skill_Animator->Play(L"axL", true);

		GameObject::Initialize();
	}
	void Ax1::Update()
	{
		dir = Vector2(500.0f, 500.0f);
		dir.Normalize();
		rotation = math::Rotate(dir, R);

		Skill_Pos.x += Ax_vel_X * rotation.x * (double)Time::getDeltaTime();
		Skill_Pos.y += Ax_vel_Y * rotation.y * (double)Time::getDeltaTime();

		Ax_vel_Y -= (double)Time::getDeltaTime() * 1300;
		Skil_Tr->setPos(Skill_Pos);


		mTime += Time::getDeltaTime();

		if (mTime > 3.0f || PlaySceneManager::Level_Up)
			object::Destory(this);

		GameObject::Update();
	}
	void Ax1::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Skill_Pos);

		GameObject::Render(hdc);
	}
	void Ax1::Release()
	{

	}
}
