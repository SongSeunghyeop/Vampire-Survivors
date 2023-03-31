#include "CharactorSelect.h"
#include "myResourceManager.h"
#include "Time.h"
#include "myInput.h"
#include "myImage.h"

namespace my
{
	CharactorSelect::CharactorSelect()
	{

	}
	CharactorSelect::~CharactorSelect()
	{

	}
	void CharactorSelect::Initialize()
	{
		SelectUI = ResourceManager::Load<Image>(L"SelectUI", L"..\\Resources\\SelectUI.bmp");
		Title = ResourceManager::Load<Image>(L"Title", L"..\\Resources\\Title.bmp");
		Money = ResourceManager::Load<Image>(L"Money", L"..\\Resources\\Money.bmp");

		GameObject::Initialize();
	}
	void CharactorSelect::Update()
	{
		GameObject::Update();

	}
	void CharactorSelect::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* trans = GetComponent<Transform>();
		Vector2 pos = trans->getPos();

		//1500//750
		StretchBlt(hdc, 120, 0, 1260, 750, Title->GetHdc(), 0, 0, Title->GetWidth(),Title->GetHeight(), SRCCOPY);
		StretchBlt(hdc, 400, 100, 700, 550, SelectUI->GetHdc(), 0, 0, SelectUI->GetWidth(), SelectUI->GetHeight(), SRCCOPY);
	}
	void CharactorSelect::Release()
	{
		GameObject::Release();
	}
}