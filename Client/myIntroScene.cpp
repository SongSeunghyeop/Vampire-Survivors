#include "myIntroScene.h"
#include "mySceneManager.h"
#include "Intro.h"
#include "CharactorSelect.h"
#include "myCollisionManager.h"

namespace my
{

	IntroScene::IntroScene()
	{

	}
	IntroScene::~IntroScene()
	{

	}
	void IntroScene::Initialize()
	{
		object::Instantiate<Intro>(Vector2::Zero, eLayerType::BACKGROUND);
	}
	void IntroScene::Update()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::LBUTTON; i++)
		{
        	if (Input::GetKeyState((eKeyCode)i) == eKeyState::Down)
			{
				SceneManager::LoadScene(eSceneType::Title); // 바로 화면 전환
			}
		}

		Vector2 mPos = Input::GetMousePos();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (mPos.x > 3 && mPos.x < 1277 && mPos.y > 3 && mPos.y < 710)
				SceneManager::LoadScene(eSceneType::Title); // 바로 화면 전환
		}
		Scene::Update();
	}
	void IntroScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void IntroScene::Release()
	{
		Scene::Release();
	}

	void IntroScene::OnEnter()
	{

	}
	void IntroScene::OnExit()
	{

	}
}