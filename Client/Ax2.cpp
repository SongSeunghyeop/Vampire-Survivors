#include "Ax2.h"
#include "PlaySceneManager.h"

namespace my
{
	Ax2::Ax2()
	{
		this->setName(L"Ax1");
		Skill_Vel = 450.0f;
		mTime = 0.0f;
	}
	Ax2::~Ax2()
	{

	}
	void Ax2::Initialize()
	{
		Skill_Image = ResourceManager::Load<Image>(L"BaseBullet", L"..\\Resources\\ax_All.bmp");

		Skil_Tr = GetComponent<Transform>();
		Skil_Tr->setScale(5, 5);
		Skill_Pos = Skil_Tr->getPos();
		
		Skill_Collider = AddComponent<Collider>();
		Skill_Collider->setCenter(Vector2(1, -9));
		Skill_Collider->setSize(Vector2(75, 75));
		Skill_Collider->setRGB(0, 0, 255);

		Skill_Animator = AddComponent<Animator>(); 
		Skill_Animator->CreateAnimation(L"ax", Skill_Image, Vector2::Zero, 8, 1, 8, 0.05, 255, 0, 255);
		Skill_Animator->CreateAnimation(L"ax_stop", Skill_Image, Vector2::Zero, 8, 1, 1, 0.05, 255, 0, 255);
		Skill_Animator->Play(L"ax", true);
		
		GameObject::Initialize();
	}
	void Ax2::Update()
	{
		dir = Vector2(500.0f, 500.0f);
		dir.Normalize();
		rotation = math::Rotate(dir, R);

		Skill_Pos.x += Skill_Vel * rotation.x * (double)Time::getDeltaTime();
		Skill_Pos.y += Skill_Vel * rotation.y * (double)Time::getDeltaTime();

		Skil_Tr->setPos(Skill_Pos);

		if (mTime > 3.5f)
			object::Destory(this);

		if (PlaySceneManager::Level_Up)
		{
			Skill_Animator->Play_NO_RE(L"ax_stop", false);
			Skill_Vel = 0.0f;
		}
		else
		{
			mTime += Time::getDeltaTime();

			Skill_Animator->Play_NO_RE(L"ax", true);
			Skill_Vel = 450.0f;
		}

		GameObject::Update();
	}
	void Ax2::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Skill_Pos);

		GameObject::Render(hdc);
	}
	void Ax2::Release()
	{

	}
}
