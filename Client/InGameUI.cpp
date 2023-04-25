#include "InGameUI.h"
#include "myObject.h"
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
		cutton = object::Instantiate<Cutton>
			(eLayerType::UI);
		menu = object::Instantiate<GameOption>
			(eLayerType::UI);
	}
	void Option::Update()
	{
		if (Input::GetKeyState(eKeyCode::ESC) == eKeyState::Down)
		{
			cutton->setCutton(false);
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