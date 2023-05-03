#include "Treasure.h"
#include "Treasure_Arrow.h"
#include "myObject.h"

namespace my
{
	Treasure::Treasure()
	{
		setName(L"Treasure");
	}
	void Treasure::Initialize()
	{
		treasure = ResourceManager::Load<Image>(L"Treasure", L"..\\Resources\\Treasure.bmp");
		
		Vector2 RandPos;
		RandPos.x = rand() % 1000 - 500;  // -500 ~ 500
		RandPos.y = rand() % 4800 - 2400; //  -2400 ~ 2400

		while (RandPos.y > -2300 && RandPos.y < 2300) // 2300
		{
			RandPos.x = rand() % 1000 - 500;  // -500 ~ 500
			RandPos.y = rand() % 4800 - 2400; //  -2400 ~ 2400
		}

		Item_TR = GetComponent<Transform>();
		Item_TR->setPos(Krochi::getPlayerPos() + RandPos); // 1000,600

		Item_Collider = AddComponent<Collider>();
		Item_Collider->setCenter(Vector2(3, 43));
		Item_Collider->setSize(Vector2(38, 35));
		Item_Collider->setRGB(255, 0, 255);

		arrow = object::Instantiate<Treasure_Arrow>(Item_TR->getPos() + Vector2(5000, 5000), eLayerType::ARROW);
		arrow->SetTreasure(this);

		GameObject::Initialize();
	}

	void Treasure::Update()
	{
		treasurePos = Item_TR->getPos(); // Vector2(1000,600) 아닐시 문제 생길 수 있음

		if (treasurePos.y > Krochi::getPlayerPos().y + 380)
		{
			treasure_Down = true;
		}
		else
		{
			treasure_Down = false;
		}
		if (treasurePos.y < Krochi::getPlayerPos().y - 392)
		{
			treasure_Up = true;
		}
		else
		{
			treasure_Up = false;
		}
		if (treasurePos.x > Krochi::getPlayerPos().x + 633
			&& treasurePos.y > Krochi::getPlayerPos().y - 370
			&& treasurePos.y < Krochi::getPlayerPos().y + 360
			)
		{
			treasure_Right = true;
		}
		else
		{
			treasure_Right = false;
		}
		if (treasurePos.x <  Krochi::getPlayerPos().x - 631
			&& treasurePos.y > Krochi::getPlayerPos().y - 370
			&& treasurePos.y < Krochi::getPlayerPos().y + 360)
		{
			treasure_Left = true;
		}
		else
		{
			treasure_Left = false;
		}

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
			object::Destory(arrow);
			object::Destory(this);
		}
	}
}