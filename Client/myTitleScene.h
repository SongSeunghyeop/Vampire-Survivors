#pragma once
#include "TitleUI.h"
#include "Title.h"
#include "myScene.h"
#include "myObject.h"

namespace my
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();

	private:
		Title* title;
		TitleUI* cs;
	};
}