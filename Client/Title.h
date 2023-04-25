#pragma once
#include "MyGameObject.h"
#include "myTransform.h"
#include "myAnimator.h"
#include "TitleUI.h"

namespace my
{
	class Title : public GameObject
	{
	public:
		Title();
		~Title();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		static bool TitleUIButton;

	private:
		Image* titleImg;
		Image* start;
		Image* start_M;
		Image* Exit;
		Image* Option;
		Image* SelectUI;
		Image* Option_Button;
		Image* Exit_Button;
		Image* Select_Button;
		Vector2 mPos;
	};
}

