#pragma once
#include "MyGameObject.h"
#include "myImage.h" 
#include "myApplication.h"

namespace my
{
	class Field : public GameObject
	{
	public:
		Field();
		~Field();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		Image* fieldImg;
		float width;
		int height;
	};
}

