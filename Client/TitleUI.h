#pragma once
#include "MyGameObject.h"
#include "myImage.h" 
#include "myTransform.h"

namespace my
{
	class TitleUI : public GameObject
	{
	public:
		TitleUI();
		~TitleUI();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		static bool PlayButton;
	private:
		Image* titleImg;
		Image* SelectUI;
		Image* start;
		Image* start_M;
		Image* info;
		Image* Selection;
		Image* Select_Button;


		Vector2 mPos;
	};
}

