#include "myTitleScene.h"
#include "myScene.h"
#include "mySceneManager.h"


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
			Title::TitleUIButton = false;

			TitleUI* titleUI = new TitleUI;
			titleUI->setName(L"TitleUI");
			AddGameObj(titleUI, eLayerType::BACKGROUND);
		}
		if (TitleUI::PlayButton)
		{
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