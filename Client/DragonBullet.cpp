#include "DragonBullet.h"

namespace my
{
	DragonBullet::DragonBullet()
		: mTime(0.0f)
	{
		this->setName(L"dBullet");
		bullet_vel = 500.0f;
	}

	void DragonBullet::Initialize()
	{
		bullet_Image = ResourceManager::Load<Image>(L"dBullet", L"..\\Resources\\dBullet.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->setScale(5, 5);
		bulletPos = tr->getPos();

		Collider* collider = AddComponent<Collider>();
		collider->setCenter(Vector2(0, 0));
		collider->setSize(Vector2(30, 30));
		collider->setRGB(0, 0, 255);

		GameObject::Initialize();
	}
	void DragonBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		bulletPos = tr->getPos();
		bulletPos +=  (Krochi::getPlayerPos() - tr->getPos()).Normalize()* 210* Time::getDeltaTime();
		tr->setPos(bulletPos);

		mTime += Time::getDeltaTime();

		if (mTime > 4.0f)
			object::Destory(this);

		GameObject::Update();
	}
	void DragonBullet::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(bulletPos);

		TransparentBlt(hdc, pos.x, pos.y,
			bullet_Image->GetWidth() * 2.4, bullet_Image->GetHeight() * 2.4, bullet_Image->GetHdc(),
			0, 0, bullet_Image->GetWidth(), bullet_Image->GetHeight(), RGB(184, 187, 185));

		GameObject::Render(hdc);
	}
}
