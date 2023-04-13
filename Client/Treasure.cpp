#include "Treasure.h"
#include "Treasure_Arrow.h"
#include "myObject.h"
#include "Krochi.h"

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
		Item_TR->setPos(Vector2(1200,800)); // 1000,600

		Item_Collider = AddComponent<Collider>();
		Item_Collider->setCenter(Vector2(3, 43));
		Item_Collider->setSize(Vector2(38, 35));
		Item_Collider->setRGB(255, 0, 255);

		arrow = object::Instantiate<Treasure_Arrow>(Item_TR->getPos() + Vector2(5000, 5000), eLayerType::UI);
		arrow->SetTreasure(this);

		GameObject::Initialize();
	}

	void Treasure::Update()
	{
		treasurePos = Item_TR->getPos(); // Vector2(1000,600) 아닐시 문제 생길 수 있음

		setArrowDir();

		if (treasure_down)
		{
			Vector2 pos;
			pos.x = treasurePos.x + 24;
			pos.y = Krochi::getPlayerPos().y + 370;

			arrow->ArrowSetPos(pos);
		}
		else if (treasure_up)
		{
			Vector2 pos;
			pos.x = treasurePos.x + 24;
			pos.y = Krochi::getPlayerPos().y - 280;

			arrow->ArrowSetPos(pos);
		}
		else if (treasure_Right)
		{
			Vector2 pos;
			pos.x = Krochi::getPlayerPos().x + 625;
			pos.y = treasurePos.y + 78;

			arrow->ArrowSetPos(pos);
		}
		else if (treasure_Left)
		{
			Vector2 pos;
			pos.x = Krochi::getPlayerPos().x - 605;
			pos.y = treasurePos.y + 78;

			arrow->ArrowSetPos(pos);
		}
		else
		{
			arrow->ArrowSetPos(Krochi::getPlayerPos() + Vector2(5000, 5000));
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
	void Treasure::setArrowDir()
	{
		if (treasurePos.y > Krochi::getPlayerPos().y + 373
			&& treasurePos.x <  Krochi::getPlayerPos().x + 612
			&& treasurePos.x >  Krochi::getPlayerPos().x - 612)
		{
			treasure_down = true;
		}
		else
		{
			treasure_down = false;
		}
		if (treasurePos.y < Krochi::getPlayerPos().y - 392
			&& treasurePos.x <  Krochi::getPlayerPos().x + 612
			&& treasurePos.x >  Krochi::getPlayerPos().x - 612)
		{
			treasure_up = true;
		}
		else
		{
			treasure_up = false;
		}
		if (treasurePos.x > Krochi::getPlayerPos().x + 633
			&& treasurePos.y > Krochi::getPlayerPos().y - 397
			&& treasurePos.y < Krochi::getPlayerPos().y + 291
			)
		{
			treasure_Right = true;
		}
		else
		{
			treasure_Right = false;
		}
		if (treasurePos.x <  Krochi::getPlayerPos().x - 631
			&& treasurePos.y > Krochi::getPlayerPos().y - 397
			&& treasurePos.y < Krochi::getPlayerPos().y + 291)
		{
			treasure_Left = true;
		}
		else
		{
			treasure_Left = false;
		}
	}
}