#include "Boss_Hp.h"

namespace my
{
	void Boss_Hp::Initialize()
	{
		hp_bar = ResourceManager::Load<Image>(L"Boss_hp_bar", L"..\\Resources\\Boss_hp.bmp");
		hp_bar2 = ResourceManager::Load<Image>(L"Boss_hp_bar2", L"..\\Resources\\Boss_hp_black.bmp");

		GameObject::Initialize();
	}
	void Boss_Hp::Update()
	{
		GameObject::Update();
	}
	void Boss_Hp::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();

		Vector2 pos = Camera::CaluatePos(Boss::getBossPos() + Vector2(-22, 150));

		TransparentBlt(hdc, pos.x, pos.y, 160, hp_bar2->GetHeight(),
			hp_bar2->GetHdc(), 0, 0, hp_bar2->GetWidth(), hp_bar2->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, pos.x, pos.y, boss->getBoss_hp(), hp_bar->GetHeight(),
			hp_bar->GetHdc(), 0, 0, hp_bar->GetWidth(), hp_bar->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
}