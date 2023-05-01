#pragma once
#include "myResourceManager.h"
#include "myImage.h" 
#include "krochi.h"

namespace my
{
	class PlaySceneManager : public GameObject
	{
	public:
		PlaySceneManager();
		~PlaySceneManager();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		static bool Level_Up;
		static bool Show_on;
		static float Play_Time;

	private:
		Image* level_bar;
		Image* Charactor;
		Image* health;
		Image* health_zero;
		Image* Ex_value;
		Image* Item_list;
		Image* monster_icon;
		Image* Black;

		HFONT font1;
		HFONT font2;
		HFONT oldfont;

		float screen_Y = -1.0f;
	};
}

