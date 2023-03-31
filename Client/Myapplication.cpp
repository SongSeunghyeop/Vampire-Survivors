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
		mhwnd = hwnd; // �ڵ�
		mhdc = GetDC(hwnd); // HDC : ��Ʈ�ʿ� �׷��ִ� ���� 
		                                              // getDC : ���� �����찡 �����ִ� ��Ʈ���� �Ҵ�޴� DC�� �������� ��� ��
		mWidth = 1280;
		mHeight = 720;

		rect = { 0,0,mWidth,mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false); // �ػ󵵸� �Է��ϸ�, �׿� �°� ����
		
		SetWindowPos(mhwnd, NULL, 246,0, rect.right - rect.left, rect.bottom - rect.top, 0); // ������ ó�� ���� �� ũ�� �� ��ġ ����
		ShowWindow(hwnd, true); // ������ �ػ� ������ ���� �Լ�(Ÿ��Ʋ��, �׵θ�,�޴��� ���� ������ �ػ��̹Ƿ�, ������ �ʿ�)
		//������ ��ü ���� ��� �簢��

		backBuffer = CreateCompatibleBitmap(mhdc, rect.right - rect.left, rect.bottom - rect.top); // ������ hdc�� ȣȯ�Ǵ� ����� ��Ʈ���� ����(��Ʈ�� = ��ȭ��)
		backHdc = CreateCompatibleDC(mhdc); // ���� hdc�� ȣȯ�Ǹ� ������ �ʴ� �޸𸮻��� HDC�� ����
		HBITMAP defaultBmp = (HBITMAP)SelectObject(backHdc, backBuffer); // ����ۿ� ��Ʈ�� ����, �� ���ۿ� hdc�� ���� ��Ʈ�ʰ� ��ü
		DeleteObject(defaultBmp); // ������ ��Ʈ�� ���� // �غ� ��

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
   		SceneManager::Render(backHdc); // ���δ� ����ۿ� ����
		Camera::Render(backHdc);

		//������� �׸� ����(������)�� ���� ( ����� ȭ����� ��ü�� ��� ���ԵǾ ���簡 �Ǵ� ���̹Ƿ� �������� �ʴ´� 
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