#pragma once
#include "myScene.h"
#include "myScene.h"
#include "mySceneManager.h"
#include "myInput.h"
#include "myImage.h"
#include "myResourceManager.h"
#include "Sound.h"

namespace my
{
	class GameOver;

	class EndingScene : public Scene
	{
	public:
		EndingScene();
		~EndingScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();

	private:
		Image* ending;

		Sound* gameoversound;
		GameOver* gameover;
	};
}