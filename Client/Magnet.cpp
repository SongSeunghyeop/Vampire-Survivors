#include "Magnet.h"
#include "myObject.h"
#include "Magnet_Arrow.h"

namespace my
{
	Magnet::Magnet()
	{
		setName(L"Magnet");
	}
	void Magnet::Initialize()
	{
		magnet = ResourceManager::Load<Image>(L"Magnet", L"..\\Resources\\magnet.bmp");

		Vector2 RandPos;
		RandPos.x = rand() % 5800 - 2900; //  -2900 ~ 2900
		RandPos.y = rand() % 800 - 400;  // -400 ~ 400

		while (RandPos.x > -2800 && RandPos.x < 2800) // 2800
		{
			RandPos.x = rand() % 5800 - 2900; //  -2900 ~ 2900
			RandPos.y = rand() % 800 - 400;  // -400 ~ 400
		}

		Item_TR = GetComponent<Transform>();
		Item_TR->setPos(Krochi::getPlayerPos() + RandPos); // 1000,600
		Item_TR->setScale(2.0f,2.0f); 

		Item_Collider = AddComponent<Collider>();
		Item_Collider->setCenter(Vector2(-10, -18));
		Item_Collider->setSize(Vector2(37, 37));
		Item_Collider->setRGB(255, 0, 255);

		magnet_Animator = AddComponent<Animator>();
		magnet_Animator->CreateAnimation(L"magnet", magnet, Vector2::Zero, 3, 1, 3, 0.15f, 255, 0, 255);
		magnet_Animator->Play(L"magnet", true);

		arrow = object::Instantiate<Magnet_Arrow>(Item_TR->getPos() + Vector2(5000, 5000), eLayerType::ARROW);
		arrow->SetMagnet(this);

		GameObject::Initialize();
	}

	void Magnet::Update()
	{
		magnetPos = Item_TR->getPos();

		if (magnetPos.y > Krochi::getPlayerPos().y + 410)
		{
			magnet_Down = true;
		}
		else
		{
			magnet_Down = false;
		}
		if (magnetPos.y < Krochi::getPlayerPos().y - 392)
		{
			magnet_Up = true;
		}
		else
		{
			magnet_Up = false;
		}
		if (magnetPos.x > Krochi::getPlayerPos().x + 640
			&& magnetPos.y > Krochi::getPlayerPos().y - 380
			&& magnetPos.y < Krochi::getPlayerPos().y + 390
			)
		{
			magnet_Right = true;
		}
		else
		{
			magnet_Right = false;
		}
		if (magnetPos.x <  Krochi::getPlayerPos().x - 640
			&& magnetPos.y > Krochi::getPlayerPos().y - 380
			&& magnetPos.y < Krochi::getPlayerPos().y + 390)
		{
			magnet_Left = true;
		}
		else
		{
			magnet_Left = false;
		}

		GameObject::Update();
	}

	void Magnet::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Item_TR->getPos());

		GameObject::Render(hdc);
	}

	void Magnet::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			object::Destory(arrow);
			object::Destory(this);
		}
	}
}