#include "GameOver.h"
#include "myResourceManager.h"
#include "myInput.h"
#include "Time.h"
#include "myImage.h"

namespace my
{
	GameOver::GameOver()
	{

	}
	GameOver::~GameOver()
	{

	}
	void GameOver::Initialize()
	{
		gameover = ResourceManager::Load<Image>(L"gameOver", L"..\\Resources\\gameOver.bmp"); // 이미지의 키와 경로 정보를 받음
		exit_Button = ResourceManager::Load<Image>(L"exit_Button2", L"..\\Resources\\Exit_Button2.bmp"); // 이미지의 키와 경로 정보를 받음

		GameObject::Initialize();
	}
	void GameOver::Update()
	{
		GameObject::Update();
	}
	void GameOver::Render(HDC hdc)
	{
		TransparentBlt(hdc, 434, 150, gameover->GetWidth() * 1.3, gameover->GetHeight() * 1.3, gameover->GetHdc(), 0, 0, gameover->GetWidth(), gameover->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 563, 500, exit_Button->GetWidth() * 1.6, exit_Button->GetHeight() * 1.6, exit_Button->GetHdc(), 0, 0, exit_Button->GetWidth(), exit_Button->GetHeight(), RGB(182, 185, 183));

		GameObject::Render(hdc);
	}
	void GameOver::Release()
	{
		GameObject::Release();
	}
}