#include "Treasure_Arrow.h"

#pragma comment(lib, "msimg32.lib")

namespace my
{
	Treasure_Arrow::Treasure_Arrow()
	{
		this->setName(L"Arrow");
	}
	Treasure_Arrow::~Treasure_Arrow()
	{

	}

	void Treasure_Arrow::Initialize()
	{
		Arrow_D = ResourceManager::Load<Image>(L"Arrow_D", L"..\\Resources\\Arrow_D.bmp");
		Arrow_U = ResourceManager::Load<Image>(L"Arrow_U", L"..\\Resources\\Arrow_U.bmp");
		Arrow_R = ResourceManager::Load<Image>(L"Arrow_R", L"..\\Resources\\Arrow_R.bmp");
		Arrow_L = ResourceManager::Load<Image>(L"Arrow_L", L"..\\Resources\\Arrow_L.bmp");

		trea = ResourceManager::Load<Image>(L"trea", L"..\\Resources\\Treasure2.bmp");

		trea_animator = AddComponent<Animator>();
		trea_animator->CreateAnimation(L"trea", trea, Vector2::Zero, 2, 1, 2, 0.2f, 255, 0, 255);

		arrow_Tr = GetComponent<Transform>();
		trea_animator->Play(L"trea", true);
		GameObject::Initialize();
	}
	void Treasure_Arrow::Update()
	{
		arrow_Tr = GetComponent<Transform>();

		if (treasure->treasure_Down)
		{
			Vector2 pos;
			if (treasure->treasurePos.x <  Krochi::getPlayerPos().x + 612
				&& treasure->treasurePos.x >  Krochi::getPlayerPos().x - 612)
			{
				pos.x = treasure->treasurePos.x + 24;
				pos.y = Krochi::getPlayerPos().y + 370;
			}
			else if (treasure->treasurePos.x < Krochi::getPlayerPos().x - 612)
			{
				pos.x = Krochi::getPlayerPos().x - 608;
				pos.y = Krochi::getPlayerPos().y + 370;
			}
			else if (treasure->treasurePos.x > Krochi::getPlayerPos().x + 612)
			{
				pos.x = Krochi::getPlayerPos().x + 624;
				pos.y = Krochi::getPlayerPos().y + 370;
			}

			arrow_Tr->setPos(pos);
		}
		else if (treasure->treasure_Up)
		{
			Vector2 pos;

			if (treasure->treasurePos.x <  Krochi::getPlayerPos().x + 612
				&& treasure->treasurePos.x >  Krochi::getPlayerPos().x - 612)
			{
				pos.x = treasure->treasurePos.x + 24;
				pos.y = Krochi::getPlayerPos().y - 280;
			}
			else if (treasure->treasurePos.x < Krochi::getPlayerPos().x - 612)
			{
				pos.x = Krochi::getPlayerPos().x - 608;
				pos.y = Krochi::getPlayerPos().y - 280;
			}
			else if (treasure->treasurePos.x > Krochi::getPlayerPos().x + 612)
			{
				pos.x = Krochi::getPlayerPos().x + 625;
				pos.y = Krochi::getPlayerPos().y - 280;
			}

			arrow_Tr->setPos(pos);
		}
		else if (treasure->treasure_Right)
		{
			Vector2 pos;
			pos.x = Krochi::getPlayerPos().x + 625;
			pos.y = treasure->treasurePos.y + 40;

			arrow_Tr->setPos(pos);
		}
		else if (treasure->treasure_Left)
		{
			Vector2 pos;
			pos.x = Krochi::getPlayerPos().x - 605;
			pos.y = treasure->treasurePos.y + 40;

			arrow_Tr->setPos(pos);
		}
		else
		{
			arrow_Tr->setPos(Krochi::getPlayerPos() + Vector2(5000, 5000));
		}

		GameObject::Update();
	}
	void Treasure_Arrow::Render(HDC hdc)
	{
		arrow_Tr = GetComponent<Transform>();
		Vector2 pos = Camera::CaluatePos(arrow_Tr->getPos());

		if(treasure->treasure_Down)
			TransparentBlt(hdc, pos.x - 25, pos.y - 60, Arrow_D->GetWidth() * 3.8, Arrow_D->GetHeight() * 4,
				Arrow_D->GetHdc(), 0, 0, Arrow_D->GetWidth(), Arrow_D->GetHeight(), RGB(255, 0, 255));
		else if (treasure->treasure_Up)
			TransparentBlt(hdc, pos.x - 25, pos.y - 38, Arrow_U->GetWidth() * 3.8, Arrow_U->GetHeight() * 4,
				Arrow_U->GetHdc(), 0, 0, Arrow_U->GetWidth(), Arrow_U->GetHeight(), RGB(255, 0, 255));
		else if(treasure->treasure_Left)
			TransparentBlt(hdc, pos.x -20, pos.y - 45, Arrow_L->GetWidth() * 4, Arrow_L->GetHeight() * 3.8,
				Arrow_L->GetHdc(), 0, 0, Arrow_L->GetWidth(), Arrow_L->GetHeight(), RGB(255, 0, 255));
		else if (treasure->treasure_Right)
			TransparentBlt(hdc, pos.x - 35, pos.y - 45, Arrow_R->GetWidth() * 4, Arrow_R->GetHeight() * 3.8,
				Arrow_R->GetHdc(), 0, 0, Arrow_R->GetWidth(), Arrow_R->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
	void Treasure_Arrow::Release()
	{
		GameObject::Release();
	}
}