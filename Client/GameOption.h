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

	private:
		Image* menuImg;
		Image* black;
	};
}

