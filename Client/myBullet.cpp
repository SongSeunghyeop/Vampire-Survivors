#include "myBullet.h"
#include "myTransform.h"
#include "Time.h"
#include "myObject.h"

namespace my
{
	BaseBullet::BaseBullet()
		: mTime(0.0f)
		, effect_Time(0.0f)
	{
	}
	BaseBullet::~BaseBullet()
	{
	}
	void BaseBullet::Initialize()
	{
		Bullet = ResourceManager::Load<Image>(L"BaseBullet", L"..\\Resources\\baseBullet.bmp");
		D_effect = ResourceManager::Load<Image>(L"D_effect", L"..\\Resources\\D_effect.bmp");

		R = rand() % 360 + 1;
		Transform * tr = GetComponent<Transform>();
		bulletPos = tr->getPos();

		Collider* collider = AddComponent<Collider>();
		collider->setCenter(Vector2(1, 0));
		collider->setSize(Vector2(33, 31));
		collider->setRGB(0, 0, 255);

		BulletColl = false;

		GameObject::Initialize();
	}
	void BaseBullet::Update()
	{
		/*float x = cosf(-PI / 4.0f);
		float y = sinf(-PI / 4.0f);*/
		//float x = dir.x * cosf(PI / 5.0f) - dir.y * sinf(PI / 5.0f);
		//float y = dir.x * sinf(PI / 5.0f) + dir.y * cosf(PI / 5.0f);

		Vector2 dir = Vector2(500.0f, 500.0f);
		dir.Normalize();
		Vector2 ro = math::Rotate(dir, R);
		Transform* tr = GetComponent<Transform>();
		bulletPos.x += 240.0f * ro.x * (double)Time::getDeltaTime();
		bulletPos.y += 240.0f * ro.y * (double)Time::getDeltaTime();
		tr->setPos(bulletPos);

		mTime += Time::getDeltaTime();

		if (mTime >4.0f)
		{
			object::Destory(this);
		}
		GameObject::Update();
	}
	void BaseBullet::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(bulletPos);

		TransparentBlt(hdc, (int)pos.x, (int)pos.y, Bullet->GetWidth() * 1.8, Bullet->GetHeight() * 1.7, Bullet->GetHdc(), 0, 0,
			Bullet->GetWidth(), Bullet->GetHeight(), RGB(255, 0, 255));

		if (BulletColl)
		{
			Vector2 pos = Camera::CaluatePos(EnemyPos);
			effect_Time += (float)Time::getDeltaTime() * 0.3f;
			TransparentBlt(hdc, (int)pos.x, (int)pos.y, D_effect->GetWidth() * 3, D_effect->GetHeight() * 3, D_effect->GetHdc(), 0, 0,
				D_effect->GetWidth(), D_effect->GetHeight(), RGB(180, 183, 181));

			if (effect_Time >=0.1f)
			{
				BulletColl = false;
				effect_Time = 0.0f;
			}
		}

		GameObject::Render(hdc);
	}
	void BaseBullet::Release()
	{

	}
	void BaseBullet::onCollisionEnter(Collider* other)
	{
		BulletColl = true;
		EnemyPos = other->getPos();
	}

	void BaseBullet::onCollisionStay(Collider* other)
	{
		
	}

	void BaseBullet::onCollisionExit(Collider* other)
	{
		//BulletColl = false;
	}
}
