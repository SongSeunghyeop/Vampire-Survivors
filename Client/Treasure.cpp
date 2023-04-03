#include "Treasure.h"
#include "Krochi.h"

namespace my
{
	Treasure::Treasure()
	{
		setName(L"Treasure");
	}
	void Treasure::Initialize()
	{
		option = ResourceManager::Load<Image>(L"Treasure_Option", L"..\\Resources\\Option.bmp");
	
		Item_TR = GetComponent<Transform>();
		Item_TR->setPos(Krochi::getPlayerPos() + Vector2(5,320) );

		Item_Collider = AddComponent<Collider>();
		Item_Collider->setSize(Vector2(30.0f, 26.0f));
		Item_Collider->setCenter(Vector2(1.0f, 31.0f));
		Item_Collider->setRGB(255, 0, 255);

		Treasure_show = AddComponent<Animator>();
		Treasure_show->CreateAnimations(L"..\\Resources\\Treasures\\Show", 0.08f);
		Treasure_show->Play(L"TreasuresShow", false);
	}
	void Treasure::Update()
	{
		GameObject::Update();
	}
	void Treasure::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Krochi::getPlayerPos() + Vector2(-250,-280));

		TransparentBlt(hdc, pos.x, pos.y,
			option->GetWidth(), option->GetHeight(), option->GetHdc(),
			0, 0, option->GetWidth(), option->GetHeight(), RGB(255, 0, 255));

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