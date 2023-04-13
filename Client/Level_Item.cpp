#include "Level_Item.h"
#include "Effect2.h"
#include "EnemyManager.h"

namespace my
{
	Level_Item::Level_Item()
	{
		setName(L"Level_Item");
	}
	void Level_Item::Initialize()
	{
		Item_Image = ResourceManager::Load<Image>(L"Level_Item", L"..\\Resources\\item1.bmp");
		Item_TR = GetComponent<Transform>();

		Item_Collider = AddComponent<Collider>();
		Item_Collider->setSize(Vector2(15.0f,23.0f));
		Item_Collider->setRGB(255, 0, 255);

	}
	void Level_Item::Update()
	{
		if (EnemyManager::Boss_on)
		{
			/*Effect2 *effect = object::Instantiate<Effect2>
				(Item_TR->getPos() + Vector2(3.0f, 0.0f), eLayerType::EFFECT);*/

			object::Destory(this);
		}
		GameObject::Update();
	}
	void Level_Item::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Item_TR->getPos());

		TransparentBlt(hdc, pos.x, pos.y,
			Item_Image->GetWidth() * 1.8f, Item_Image->GetHeight() * 1.7f, Item_Image->GetHdc(),
			0, 0, Item_Image->GetWidth(), Item_Image->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void Level_Item::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			object::Destory(this);
		}
	}
}