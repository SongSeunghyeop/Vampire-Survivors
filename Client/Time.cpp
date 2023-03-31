#include "Time.h"
#include "myapplication.h"

extern my::Application myapplication; // �ܺκ���
																// �ܺ��� cpp���Ͽ� ���� �� ���ǵ� ���������� �ٸ� cpp���Ͽ��� ����ϰ� ���� ��, exturn Ŭ���� ������ �������� 
															    // ��� ����
namespace my
{
	double Time::deltaTime = 0.01;
	double Time::mSecond = 0.0f;
	LARGE_INTEGER Time::mCpuFreq = {};
	LARGE_INTEGER Time::mprevCpuFreq = {};
	LARGE_INTEGER Time::mcurCpuFreq = {};

	void Time::Initialize()
	{
		QueryPerformanceFrequency(&mCpuFreq); // Cpu ���� ������
		QueryPerformanceCounter(&mprevCpuFreq); // �������α׷��� ó�� ������ �� Cpu
	}
	void Time::Update()
	{
		QueryPerformanceCounter(&mcurCpuFreq); // ���� ���� ���� cpu ��� üũ

		double difference = mcurCpuFreq.QuadPart - mprevCpuFreq.QuadPart; // ���� cpu���� ó�� ���� cpu��ŭ �� ��
		deltaTime = difference / mCpuFreq.QuadPart; // �� ���� ���� cpu ������ ������ �� ���� �������� ���� ����
		mprevCpuFreq.QuadPart = mcurCpuFreq.QuadPart; // ��ŸŸ���� ������ �ڿ� ó�� ���� ���簪���� �������־�� ��� ���� ����
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