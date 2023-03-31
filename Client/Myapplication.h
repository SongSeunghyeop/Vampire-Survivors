#pragma once
#include "VampireEngine.h"

//������ ��ü�� �Ѱ�

namespace my
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Initialize(HWND mhwnd); // �ʱ�ȭ
		void Run(); // update, render
		void Update(); // ���� ����
		void Render(); // ȭ�� ����
		//void Release(); // ���� ����, �޸� ����

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
		HDC mhdc; // ����(������)
		HBITMAP backBuffer; 
		HDC backHdc; // �޸𸮻��� ����� (������ ����)
		HWND mToolHwnd;
		HMENU mMenubar;

		int mWidth;
		int mHeight;
	};
}