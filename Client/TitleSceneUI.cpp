#include "TitleSceneUI.h"
#include "myScene.h"
#include "mySceneManager.h"
#include "CharactorSelect.h"

namespace my
{
	TitleSceneUI::TitleSceneUI()
	{

	}
	TitleSceneUI::~TitleSceneUI()
	{

	}
	void TitleSceneUI::Initialize()
	{
		CharactorSelect* cs = new CharactorSelect();
		cs->SetName(L"cs");
		AddGameObj(cs, eLayerType::UI);
		Scene::Initialize();
	}
	void TitleSceneUI::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::ESC) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
	}
	void TitleSceneUI::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void TitleSceneUI::Release()
	{
		Scene::Release();
	}

	void TitleSceneUI::OnEnter()
	{

	}
	void TitleSceneUI::OnExit()
	{

	}
}