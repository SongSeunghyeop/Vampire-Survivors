#pragma once
#include "VampireEngine.h"

//게임의 전체를 총괄

namespace my
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Initialize(HWND mhwnd); // 초기화
		void Run(); // update, render
		void Update(); // 로직 실행
		void Render(); // 화면 구현
		//void Release(); // 게임 종료, 메모리 해제

		HWND GetHwnd() { return mhwnd; }
		HDC		GetHdc() { return mhdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	public:
		Vector2 getWindowPos() { return WindowPos; }

		void SetToolHwnd(HWND hwnd) { mToolHwnd = hwnd; }
		void SetMenuBar(bool power);
	private:
		void clear();
	private:
		RECT rect;
		Vector2 WindowPos;
		Vector2 mPos;
		HWND mhwnd;
		HDC mhdc; // 원본(구현용)
		HBITMAP backBuffer; 
		HDC backHdc; // 메모리상의 백버퍼 (보이지 않음)
		HWND mToolHwnd;
		HMENU mMenubar;

		int mWidth;
		int mHeight;
	};
}