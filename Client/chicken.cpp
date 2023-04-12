#include "Chicken.h"
#include "Effect2.h"
#include "EnemyManager.h"

namespace my
{
	Chicken::Chicken()
	{
		setName(L"Chicken");
	}
	void Chicken::Initialize()
	{
		Item_Image = ResourceManager::Load<Image>(L"Chicken", L"..\\Resources\\Chicken.bmp");
		Item_TR = GetComponent<Transform>();

		Item_Collider = AddComponent<Collider>();
		Item_Collider->setSize(Vector2(30.0f, 26.0f));
		Item_Collider->setRGB(255, 0, 255);

	}
	void Chicken::Update()
	{
		if (EnemyManager::Boss_on)
		{
			Effect2* effect = object::Instantiate<Effect2>
				(Item_TR->getPos() + Vector2(3.0f, 0.0f), eLayerType::EFFECT);

			object::Destory(this);
		}
		GameObject::Update();
	}
	void Chicken::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Item_TR->getPos());

		TransparentBlt(hdc, pos.x, pos.y,
			Item_Image->GetWidth() * 1.8f, Item_Image->GetHeight() * 1.7f, Item_Image->GetHdc(),
			0, 0, Item_Image->GetWidth(), Item_Image->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void Chicken::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			object::Destory(this);
		}
	}
}