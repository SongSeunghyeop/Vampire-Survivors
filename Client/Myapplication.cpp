#include "myApplication.h"
#include "mySceneManager.h"
#include "myCollisionManager.h"
#include "Time.h"
#include "myInput.h"

namespace my 
{
	Application::Application()
		: mhwnd(NULL), mhdc(NULL)
	{

	}
	Application::~Application()
	{
		SceneManager::Release();
	}

	void Application::Initialize(HWND hwnd)
	{
		mhwnd = hwnd; // 핸들
		mhdc = GetDC(hwnd); // HDC : 비트맵에 그려주는 역할 
		                                              // getDC : 현재 윈도우가 갖고있는 비트맵을 할당받는 DC가 목적지로 삼는 것
		mWidth = 1280;
		mHeight = 720;

		rect = { 0,0,mWidth,mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false); // 해상도를 입력하면, 그에 맞게 수정
		
		SetWindowPos(mhwnd, NULL, 246,0, rect.right - rect.left, rect.bottom - rect.top, 0); // 윈도우 처음 시작 시 크기 및 위치 조정
		ShowWindow(hwnd, true); // 윈도우 해상도 조절을 위한 함수(타이틀바, 테두리,메뉴바 등을 포함한 해상도이므로, 조절이 필요)
		//윈도우 전체 덮을 흰색 사각형

		backBuffer = CreateCompatibleBitmap(mhdc, rect.right - rect.left, rect.bottom - rect.top); // 현재의 hdc에 호환되는 백버퍼 비트맵을 만듦(비트맵 = 도화지)
		backHdc = CreateCompatibleDC(mhdc); // 현재 hdc에 호환되며 보이지 않는 메모리상의 HDC를 만듦
		HBITMAP defaultBmp = (HBITMAP)SelectObject(backHdc, backBuffer); // 백버퍼용 비트맵 선택, 백 버퍼용 hdc의 기존 비트맵과 교체
		DeleteObject(defaultBmp); // 기존의 비트맵 삭제 // 준비 끝

		GetClientRect(mhwnd, &rect);
		WindowPos.x = rect.right - rect.left;
		WindowPos.y = rect.bottom - rect.top;

		Time::Initialize();
		Input::Initialize();
		SceneManager::Initialize();
  		Camera::Initiailize();

		SetMenuBar(false);
	}
	void Application::Run()
	{
		Update(); 
		Render();
		SceneManager::Destroy();
	}
	void Application::Update()
	{
		GetClientRect(mhwnd, &rect);
		WindowPos.x = rect.right - rect.left;
 		WindowPos.y = rect.bottom - rect.top;

		Time::Update();
		Input::Update();
 		Camera::Update();

		SceneManager::Update();
 		CollisionManager::Update();
	}
	void Application::Render()
	{
		clear();

		Time::Render(backHdc);
		Input::Render(backHdc);
   		SceneManager::Render(backHdc); // 전부다 백버퍼에 랜더
		Camera::Render(backHdc);

		//백버퍼의 그림 원본(구현용)에 복사 ( 흰색의 화면까지 전체가 계속 포함되어서 복사가 되는 것이므로 깜빡이지 않는다 
		StretchBlt(mhdc, 0, 0, WindowPos.x, WindowPos.y, backHdc, 0, 0, 1280, 720, SRCCOPY); //1500
	}

	void Application::SetMenuBar(bool power)
	{
		SetMenu(mhwnd, mMenubar);

		RECT rect = { 0, 0, mWidth , mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, power);
	}
	void Application::clear()
	{
		HBRUSH BlackBrush = CreateSolidBrush(RGB(0,0,0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(backHdc, BlackBrush);
		Rectangle(backHdc, -1, -1, 1282, 722);
		SelectObject(backHdc, oldBrush);
		DeleteObject(BlackBrush);
	}
}