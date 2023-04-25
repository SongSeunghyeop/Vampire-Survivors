#include "Cross.h"

namespace my
{
	Cross::Cross()
	{
		this->setName(L"Cross");
		Skill_Vel = 600.0f;
		mTime = 0.0f;

		skill_sound
			= ResourceManager::Load<Sound>(L"cross_sound", L"..\\Resources\\Sound\\swing_004.wav");
		skill_sound->SetVolume(200);
		//cross_sound->Play(false);
	}
	Cross::~Cross()
	{

	}
	void Cross::Initialize()
	{
		Skill_Image = ResourceManager::Load<Image>(L"Cross", L"..\\Resources\\cross.bmp");
		
		Skil_Tr = GetComponent<Transform>();
		float y = skill_scale * 16.6;
		Skil_Tr->setScale(skill_scale, skill_scale);
		Skill_Pos = Skil_Tr->getPos();
		int width = Skill_Image->GetWidth() / 2;
		int height = Skill_Image->GetHeight();

		Skill_Collider = AddComponent<Collider>();
		Skill_Collider->setCenter(Vector2(-width / 2 + 5, -height + 5));
		Skill_Collider->setSize(Vector2(y, y));
		Skill_Collider->setRGB(0, 255,0); 

		Skill_Animator = AddComponent<Animator>();
		Skill_Animator->CreateAnimation(L"Cross", Skill_Image, Vector2::Zero, 2, 1, 2, 0.04f, 255, 0, 255);
		Skill_Animator->Play(L"Cross", true);

		GameObject::Initialize();
	}
	void Cross::Update()
	{
		dir = Vector2(500.0f, 500.0f);
		dir.Normalize();
		rotation = math::Rotate(dir, R);

		Skill_Pos.x += Skill_Vel * rotation.x * (double)Time::getDeltaTime();
		Skill_Pos.y += Skill_Vel * rotation.y * (double)Time::getDeltaTime();
		Skil_Tr->setPos(Skill_Pos);

		mTime += Time::getDeltaTime();
		
		if (mTime > 0.05f)
			Skill_Vel -= Time::getDeltaTime() * 1300.0f;

		if (mTime > 2.5f)
			object::Destory(this);

		GameObject::Update();
	}
	void Cross::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Skill_Pos);

		GameObject::Render(hdc);
	}
	void Cross::Release()
	{

	}
}
