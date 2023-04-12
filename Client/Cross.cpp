#include "Cross.h"
#include "Time.h"
#include "myObject.h"

namespace my
{
	Cross::Cross()
		: mTime(0.0f)
		, effect_Time(0.0f)
	{
		this->setName(L"Cross");
		bullet_vel = 250.0f;

	}
	Cross::~Cross()
	{

	}
	void Cross::Initialize()
	{
		ax_Image = ResourceManager::Load<Image>(L"Cross", L"..\\Resources\\cross.bmp");
		
		Transform* tr = GetComponent<Transform>();
		float y = cross_scale * 16.6;
		tr->setScale(cross_scale, cross_scale);
		bulletPos = tr->getPos();
		int width = ax_Image->GetWidth() / 2;
		int height = ax_Image->GetHeight();

		Collider* collider = AddComponent<Collider>();
		collider->setCenter(Vector2(-width / 2 + 5, -height + 5));
		collider->setSize(Vector2(y, y));
		collider->setRGB(0, 255,0);

		Ax_Animator = AddComponent<Animator>();
		Ax_Animator->CreateAnimation(L"Cross", ax_Image, Vector2::Zero, 2, 1, 2, 0.045f, 255, 0, 255);
		Ax_Animator->Play(L"Cross", true);

		GameObject::Initialize();
	}
	void Cross::Update()
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
		
		if (mTime > 0.5f)
		{
			bullet_vel -= Time::getDeltaTime() * 540.0f;
		}
		if (mTime > 4.0f)
		{
			object::Destory(this);
		}
		GameObject::Update();
	}
	void Cross::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(bulletPos);

		GameObject::Render(hdc);
	}
	void Cross::Release()
	{

	}
	void Cross::onCollisionEnter(Collider* other)
	{

	}

	void Cross::onCollisionStay(Collider* other)
	{

	}

	void Cross::onCollisionExit(Collider* other)
	{

	}
}
