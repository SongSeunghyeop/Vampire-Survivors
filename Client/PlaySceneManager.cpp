#include "PlaySceneManager.h"
#include "myInput.h"
#include "myPlayScene.h"
#include "Sound.h"
namespace my
{
	bool PlaySceneManager::Level_Up;
	bool PlaySceneManager::Show_on;
	float PlaySceneManager::Play_Time;

	Krochi::eSkillState Krochi::skillState;

	PlaySceneManager::PlaySceneManager()
	{
		Play_Time = 0.0f;

		font1 = CreateFont(29, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"돋움체");
		font2 = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"돋움체");
	}
	PlaySceneManager::~PlaySceneManager()
	{

	}
	void PlaySceneManager::Initialize()
	{
		// 인 게임 플레이어 체력, 경험치 등 UI
		level_bar = ResourceManager::Load<Image>(L"levelBar", L"..\\Resources\\InGameBar_.bmp");
		Charactor = ResourceManager::Load<Image>(L"charactor", L"..\\Resources\\Arca.bmp");
		health = ResourceManager::Load<Image>(L"health", L"..\\Resources\\health.bmp");
		health_zero = ResourceManager::Load<Image>(L"health_z", L"..\\Resources\\health_zero.bmp");
		Ex_value = ResourceManager::Load<Image>(L"Ex_value", L"..\\Resources\\Ex_value.bmp");
		Item_list = ResourceManager::Load<Image>(L"Item_list", L"..\\Resources\\Item_list.bmp");
		monster_icon = ResourceManager::Load<Image>(L"monster_icon", L"..\\Resources\\monster_icon.bmp");
		Black = ResourceManager::Load<Image>(L"Black", L"..\\Resources\\Black.bmp");
	
		GameObject::Initialize();
	}
	void PlaySceneManager::Update()
	{
		// 레벨업을 했거나, 보물 상자를 열었을 때, 스킬 일시 정지
		if (PlaySceneManager::Level_Up || PlaySceneManager::Show_on)
		{
			Krochi::skillState = Krochi::eSkillState::Skill_Off;
		}
		//레벨업, 보물상자 오픈 외의 상황에서만 플레이 타임이 흐름
		if (!PlaySceneManager::Level_Up && !PlaySceneManager::Show_on)
		{
			Play_Time += Time::getDeltaTime();
			Krochi::skillState = Krochi::eSkillState::Skill_On;
		}
		
		GameObject::Update();
	}

	void PlaySceneManager::Render(HDC hdc)
	{
		if (PlaySceneManager::Play_Time > EnemyManager::boss_Time - 5.0f && !EnemyManager::Boss_on)
		{
			if (screen_Y <= 120)
				screen_Y += Time::getDeltaTime() * 60.0f;
		}
		if (PlaySceneManager::Play_Time > EnemyManager::boss_Time + 6.6f && EnemyManager::Boss_on)
		{
			if (screen_Y >= 70)
				screen_Y -= Time::getDeltaTime() * 200.0f;
		}

		TransparentBlt(hdc, -1, screen_Y - 120, 1301, 121,
			Black->GetHdc(), 0, 0, Black->GetWidth(), Black->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, -1, 801.0f - screen_Y, 1301, 121,
			Black->GetHdc(), 0, 0, Black->GetWidth(), Black->GetHeight(), RGB(255, 0, 255));

		//플레이어 인포 UI
		TransparentBlt(hdc, 152, 5, level_bar->GetWidth(), level_bar->GetHeight(),
			level_bar->GetHdc(), 0, 0, level_bar->GetWidth(), level_bar->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 152, 5, Krochi::Exp, Ex_value->GetHeight(),
			Ex_value->GetHdc(), 0, 0, Krochi::Exp, Ex_value->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 15, 5, Charactor->GetWidth(), Charactor->GetHeight(),
			Charactor->GetHdc(), 0, 0, Charactor->GetWidth(), Charactor->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 152, 39, Item_list->GetWidth() * 2.4, Item_list->GetHeight() * 2.4,
			Item_list->GetHdc(), 0, 0, Item_list->GetWidth(), Item_list->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 22, 120, health_zero->GetWidth(), health_zero->GetHeight(),
			health_zero->GetHdc(), 0, 0, health_zero->GetWidth(), health_zero->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 22, 120, Krochi::Hp, health->GetHeight(),
			health->GetHdc(), 0, 0, health->GetWidth(), health->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 1250, 40, monster_icon->GetWidth() * 2, monster_icon->GetHeight() * 2,
			monster_icon->GetHdc(), 0, 0, monster_icon->GetWidth(), monster_icon->GetHeight(), RGB(255, 0, 255));

		int minute = (int)Play_Time / 60;
		int second = (int)Play_Time % 60;

		std::wstringstream ss;
		ss << std::setfill(L'0') << std::setw(2) << minute << L" : " << std::setfill(L'0') << std::setw(2) << second;

		std::wstring text = ss.str();
		std::wstring text2 = L"LV " + std::to_wstring((int)Krochi::level);
		std::wstring text3 = std::to_wstring((int)Krochi::Death_count);

		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		oldfont = (HFONT)SelectObject(hdc, font1);
		TextOut(hdc, 594, 38, text.c_str(), text.length());
		SelectObject(hdc, oldfont);
		oldfont = (HFONT)SelectObject(hdc, font2);
		TextOut(hdc, 1220, 11, text2.c_str(), text2.length());
		TextOut(hdc, 1209, 40, text3.c_str(), text3.length());
		SelectObject(hdc, oldfont);

		GameObject::Render(hdc);
	}
	void PlaySceneManager::Release()
	{
		DeleteObject(font1);
		DeleteObject(font2);
	}
}