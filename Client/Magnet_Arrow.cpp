#include "Magnet_Arrow.h"

#pragma comment(lib, "msimg32.lib")

namespace my
{
	Magnet_Arrow::Magnet_Arrow()
	{
		this->setName(L"Arrow");
	}

	void Magnet_Arrow::Initialize()
	{
		Arrow_D = ResourceManager::Load<Image>(L"Arrow_D2", L"..\\Resources\\Arrow_D2.bmp");
		Arrow_U = ResourceManager::Load<Image>(L"Arrow_U2", L"..\\Resources\\Arrow_U2.bmp");
		Arrow_R = ResourceManager::Load<Image>(L"Arrow_R2", L"..\\Resources\\Arrow_R2.bmp");
		Arrow_L = ResourceManager::Load<Image>(L"Arrow_L2", L"..\\Resources\\Arrow_L2.bmp");

		mag = ResourceManager::Load<Image>(L"mag", L"..\\Resources\\magnet2.bmp");

		mag_animator = AddComponent<Animator>();
		mag_animator->CreateAnimation(L"mag", mag, Vector2::Zero, 2, 1, 2, 0.2f, 255, 0, 255);

		arrow_Tr = GetComponent<Transform>();
		mag_animator->Play(L"mag", true);
		GameObject::Initialize();
	}
	void Magnet_Arrow::Update()
	{
		arrow_Tr = GetComponent<Transform>();

		if (magnet->magnet_Down)
		{
			Vector2 pos;
			if (magnet->magnetPos.x <  Krochi::getPlayerPos().x + 612
				&& magnet->magnetPos.x >  Krochi::getPlayerPos().x - 612)
			{
				pos.x = magnet->magnetPos.x + 5;
				pos.y = Krochi::getPlayerPos().y + 390;
			}
			else if (magnet->magnetPos.x < Krochi::getPlayerPos().x - 612)
			{
				pos.x = Krochi::getPlayerPos().x - 608;
				pos.y = Krochi::getPlayerPos().y + 390;
			}
			else if (magnet->magnetPos.x > Krochi::getPlayerPos().x + 612)
			{
				pos.x = Krochi::getPlayerPos().x + 624;
				pos.y = Krochi::getPlayerPos().y + 390;
			}

			arrow_Tr->setPos(pos);
		}
		else if (magnet->magnet_Up)
		{
			Vector2 pos;

			if (magnet->magnetPos.x <  Krochi::getPlayerPos().x + 612
				&& magnet->magnetPos.x >  Krochi::getPlayerPos().x - 612)
			{
				pos.x = magnet->magnetPos.x + 5;
				pos.y = Krochi::getPlayerPos().y - 300;
			}
			else if (magnet->magnetPos.x < Krochi::getPlayerPos().x - 612)
			{
				pos.x = Krochi::getPlayerPos().x - 608;
				pos.y = Krochi::getPlayerPos().y - 300;
			}
			else if (magnet->magnetPos.x > Krochi::getPlayerPos().x + 612)
			{
				pos.x = Krochi::getPlayerPos().x + 625;
				pos.y = Krochi::getPlayerPos().y - 300;
			}

			arrow_Tr->setPos(pos);
		}
		else if (magnet->magnet_Right)
		{
			Vector2 pos;
			pos.x = Krochi::getPlayerPos().x + 620;
			pos.y = magnet->magnetPos.y + 20;

			arrow_Tr->setPos(pos);
		}
		else if (magnet->magnet_Left)
		{
			Vector2 pos;
			pos.x = Krochi::getPlayerPos().x - 600;
			pos.y = magnet->magnetPos.y + 20;

			arrow_Tr->setPos(pos);
		}
		else
		{
			arrow_Tr->setPos(Krochi::getPlayerPos() + Vector2(5000, 5000));
		}

		GameObject::Update();
	}
	void Magnet_Arrow::Render(HDC hdc)
	{
		arrow_Tr = GetComponent<Transform>();
		Vector2 pos = Camera::CaluatePos(arrow_Tr->getPos());

		if (magnet->magnet_Down)
			TransparentBlt(hdc, pos.x - 26, pos.y - 60, Arrow_D->GetWidth() * 4, Arrow_D->GetHeight() * 4.2,
				Arrow_D->GetHdc(), 0, 0, Arrow_D->GetWidth(), Arrow_D->GetHeight(), RGB(255, 0, 255));
		else if (magnet->magnet_Up)
			TransparentBlt(hdc, pos.x - 26, pos.y - 38, Arrow_U->GetWidth() * 4, Arrow_U->GetHeight() * 4.2,
				Arrow_U->GetHdc(), 0, 0, Arrow_U->GetWidth(), Arrow_U->GetHeight(), RGB(255, 0, 255));
		else if (magnet->magnet_Left)
			TransparentBlt(hdc, pos.x - 20, pos.y - 46, Arrow_L->GetWidth() * 4.2, Arrow_L->GetHeight() * 4,
				Arrow_L->GetHdc(), 0, 0, Arrow_L->GetWidth(), Arrow_L->GetHeight(), RGB(255, 0, 255));
		else if (magnet->magnet_Right)
			TransparentBlt(hdc, pos.x - 35, pos.y - 46, Arrow_R->GetWidth() * 4.2, Arrow_R->GetHeight() * 4,
				Arrow_R->GetHdc(), 0, 0, Arrow_R->GetWidth(), Arrow_R->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
	void Magnet_Arrow::Release()
	{
		GameObject::Release();
	}
}