#include "Treasure.h"
#include "Krochi.h"
#include "LevelManager.h"

namespace my
{
	Treasure::Treasure()
	{
		setName(L"Treasure");
	}
	void Treasure::Initialize()
	{
		treasure = ResourceManager::Load<Image>(L"Treasure", L"..\\Resources\\Treasure.bmp");

		Item_TR = GetComponent<Transform>();
		Item_TR->setPos(Vector2(1000,600));

		Item_Collider = AddComponent<Collider>();
		Item_Collider->setCenter(Vector2(3, 43));
		Item_Collider->setSize(Vector2(38, 35));
		Item_Collider->setRGB(255, 0, 255);
	}

	void Treasure::Update()
	{
		GameObject::Update();
	}

	void Treasure::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Item_TR->getPos());
		TransparentBlt(hdc, pos.x, pos.y,
			treasure->GetWidth() * 2.4, treasure->GetHeight() * 2.4, treasure->GetHdc(),
			0, 0, treasure->GetWidth(), treasure->GetHeight(), RGB(255, 0, 255));
	
		GameObject::Render(hdc);
	}

	void Treasure::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			object::Destory(this);
		}
	}

	void Treasure::onCollisionStay(Collider* other)
	{

	}
	void Treasure::onCollisionExit(Collider* other)
	{

	}
}