#include "Time.h"
#include "myapplication.h"

extern my::Application myapplication; // 외부변수
																// 외부의 cpp파일에 선언 및 정의된 전역변수를 다른 cpp파일에서 사용하고 싶을 때, exturn 클래스 변수명 선언으로 
															    // 사용 가능
namespace my
{
	double Time::deltaTime = 0.01;
	double Time::mSecond = 0.0f;
	LARGE_INTEGER Time::mCpuFreq = {};
	LARGE_INTEGER Time::mprevCpuFreq = {};
	LARGE_INTEGER Time::mcurCpuFreq = {};

	void Time::Initialize()
	{
		QueryPerformanceFrequency(&mCpuFreq); // Cpu 고유 진동수
		QueryPerformanceCounter(&mprevCpuFreq); // 게임프로그램이 처음 시작할 때 Cpu
	}
	void Time::Update()
	{
		QueryPerformanceCounter(&mcurCpuFreq); // 게임 진행 동안 cpu 계속 체크

		double difference = mcurCpuFreq.QuadPart - mprevCpuFreq.QuadPart; // 현재 cpu에서 처음 시작 cpu만큼 뺀 값
		deltaTime = difference / mCpuFreq.QuadPart; // 그 값을 고유 cpu 값으로 나누면 몇 분이 지났는지 예측 가능
		mprevCpuFreq.QuadPart = mcurCpuFreq.QuadPart; // 델타타임을 구해준 뒤엔 처음 값을 현재값으로 지정해주어야 계속 측정 가능
	}
	void Time::Render(HDC hdc)
	{
		mSecond += deltaTime;

		if (mSecond > 1.0f)
		{
			HWND hWnd = myapplication.GetHwnd();

			wchar_t szFloat[50] = {};
			double FPS = 1.0f / deltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);

			mSecond = 0.0f;
		}
	}
}