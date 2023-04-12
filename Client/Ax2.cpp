#include "Ax2.h"
#include "Time.h"
#include "myObject.h"

namespace my
{
	Ax2::Ax2()
		: mTime(0.0f)
		, effect_Time(0.0f)
	{
		this->setName(L"Ax2");
		bullet_vel = 250.0f;

	}
	Ax2::~Ax2()
	{

	}
	void Ax2::Initialize()
	{
		ax_Image = ResourceManager::Load<Image>(L"BaseBullet", L"..\\Resources\\ax_All.bmp");

		Transform * tr = GetComponent<Transform>();
		tr->setScale(3, 3);
		bulletPos = tr->getPos();
		
		Collider* collider = AddComponent<Collider>();
		collider->setCenter(Vector2(-8, -15));
		collider->setSize(Vector2(50, 50));
		collider->setRGB(0, 0, 255);

		Ax_Animator = AddComponent<Animator>(); 
		Ax_Animator->CreateAnimation(L"ax", ax_Image, Vector2::Zero, 4, 1, 4, 0.1f, 255, 0, 255);
		Ax_Animator->Play(L"ax", true);
		
		GameObject::Initialize();
	}
	void Ax2::Update()
	{
		/*float x = cosf(-PI / 4.0f);
		float y = sinf(-PI / 4.0f);*/
		//float x = dir.x * cosf(PI / 5.0f) - dir.y * sinf(PI / 5.0f);
		//float y = dir.x * sinf(PI / 5.0f) + dir.y * cosf(PI / 5.0f);
		
		dir = Vector2(500.0f, 500.0f);
		dir.Normalize();
		rotation = math::Rotate(dir, R);

		Transform* tr = GetComponent<Transform>();
		bulletPos.x += bullet_vel * rotation.x * (double)Time::getDeltaTime();
		bulletPos.y += bullet_vel * rotation.y * (double)Time::getDeltaTime();
		tr->setPos(bulletPos);

		mTime += Time::getDeltaTime();

		if (mTime > 5.0f)
		{
			object::Destory(this);
		}
		GameObject::Update();
	}
	void Ax2::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(bulletPos);

		GameObject::Render(hdc);
	}
	void Ax2::Release()
	{

	}
	void Ax2::onCollisionEnter(Collider* other)
	{
	
	}

	void Ax2::onCollisionStay(Collider* other)
	{
		
	}

	void Ax2::onCollisionExit(Collider* other)
	{

	}
}
