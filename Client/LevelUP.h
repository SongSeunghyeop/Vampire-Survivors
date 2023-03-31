#pragma once
#include "MyGameObject.h"
#include "myImage.h" 
#include "Myapplication.h"

namespace my
{
	class Level_Up : public GameObject
	{
	public:
		Level_Up();
		~Level_Up();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		bool On = false;
		
	private:
		Image* menuImg;
		Image* black;
		Image* wind;
		Image* blade;
		Image* Power_up;
	};
}

