#pragma once
#include "MyGameObject.h"
#include "myImage.h" 
#include "myTransform.h"

namespace my
{
	class Intro : public GameObject
	{
	public:
		Intro();
		~Intro();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		Image* titleImg;
		Image* IntroM;

		static double mSecond;
	};
}

