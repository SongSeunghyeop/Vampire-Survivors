#pragma once
#include "MyGameObject.h"
#include "myImage.h" 
#include "myTransform.h"
#include "Myapplication.h"

namespace my
{
	class GameOption : public GameObject
	{
	public:
		GameOption();
		~GameOption();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		static float sound_v1; // À½¾Ç
		static float sound_v2; // È¿°úÀ½
	private:
		Image* menuImg;
		Image* black;
		Image* sound_line;
		Image* sound_button;

		HFONT font1;
		HFONT font2;
		HFONT oldfont;

		float button_pos1;
		float button_pos2;

		Vector2 mPos;

		bool Clicked;
	};
}

