#include "myTitleScene.h"
#include "myScene.h"
#include "mySceneManager.h"
#include "myResourceManager.h"

namespace my
{
	TitleScene::TitleScene()
	{

	}
	TitleScene::~TitleScene()
	{

	}

	void TitleScene::Initialize()
	{
		input_Sound
			= ResourceManager::Load<Sound>(L"input_Sound", L"..\\Resources\\Sound\\sfx_sounds_pause7_in.wav");

		object::Instantiate<Title>(Vector2::Zero, eLayerType::BACKGROUND);
	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		if (Title::TitleUIButton)
		{
			input_Sound->Play(false);
			Title::TitleUIButton = false;

			TitleUI* titleUI = new TitleUI;
			titleUI->setName(L"TitleUI");
			AddGameObj(titleUI, eLayerType::BACKGROUND);
			titleUI->Initialize();
		}
		if (TitleUI::PlayButton)
		{
			input_Sound->Play(false);
			TitleUI::PlayButton = false;
			SceneManager::LoadScene(eSceneType::Play);
		}
	}
	void TitleScene::Release()
	{
		Scene::Release();
	}

	void TitleScene::OnEnter()
	{

	}
	void TitleScene::OnExit()
	{

	}
}