#pragma once
#include "myScene.h"
#include "myInput.h"
#include "myObject.h"
#include "Sound.h"
namespace my
{
	class IntroScene : public Scene
	{
	public:
		IntroScene();
		~IntroScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();
	private:
		Sound* input_Sound;
		Sound* mainTheme;
	};
}