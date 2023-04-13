#include "Radar.h"
#include "myAnimation.h"

#pragma comment(lib, "msimg32.lib")

extern my::Application myapplication;

namespace my
{
	std::vector<Collider*> Radar::Enemies;

	Radar::Radar()
	{
		this->setName(L"Radar");

		Radar_Size.x = 1270; 
		Radar_Size.y = 710;	
	}
	Radar::~Radar()
	{

	}

	void Radar::Initialize()
	{
		radar_Collider = AddComponent<Collider>();
		radar_Collider->setSize(Radar_Size);
		radar_Collider->setCenter(Radar_Size / 2 * (-1) + Vector2(10,10));

		rader_Tr = GetComponent<Transform>();

		GameObject::Initialize();
	}
	void Radar::Update()
	{
		rader_Tr->setPos(Krochi::Playerpos);

		GameObject::Update();
	}
	void Radar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Radar::Release()
	{
		GameObject::Release();
	}
	void Radar::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Enemy")
		{
			Enemies.push_back(other);
		}
	}
	void Radar::onCollisionStay(Collider* other)
	{ 
		if (other->getOwner()->getName() == L"Enemy")
		{
			radar_Collider->setRGB(255, 0, 0);

			if(other->getOwner()->getState() == GameObject::eState::Death)
				myErase(other);
		}
	}
	void Radar::onCollisionExit(Collider* other)
	{
		if (other->getOwner()->getName() == L"Enemy")
		{
		radar_Collider->setRGB(0, 255, 0);
		myErase(other);
		}
	}
}