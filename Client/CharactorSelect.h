#pragma once
#include "MyGameObject.h"
#include "myImage.h" 
#include "myTransform.h"

namespace my
{
	class CharactorSelect : public GameObject
	{
	public:
		CharactorSelect();
		~CharactorSelect();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		Image* SelectUI;
		Image* Title;
		Image* Money;
	};
}

