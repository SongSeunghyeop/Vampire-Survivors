#pragma once
#include "MyGameObject.h"
#include "myImage.h" 
#include "myTransform.h"

namespace my
{
	class GameOver : public GameObject
	{
	public:
		GameOver();
		~GameOver();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		Image* gameover;
		Image* exit_Button;
	};
}

