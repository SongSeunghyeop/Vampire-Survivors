#include "InGameUI.h"

namespace my
{
	Option::Option()
	{
	
	}
	Option::~Option()
	{

	}
	void Option::Initialize()
	{
		menu = new GameOption();

		AddGameObj(menu, eLayerType::UI);

		menu->Initialize();
	}
	void Option::Update()
	{

		if (Input::GetKeyState(eKeyCode::ESC) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
			Input::SetKeyState(eKeyCode::ESC, eKeyState::None);
		}

		Scene::Update();
	}
	void Option::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Option::Release()
	{
		Scene::Release();
	}
}