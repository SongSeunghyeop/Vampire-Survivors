#include "myIntroScene.h"
#include "mySceneManager.h"
#include "Intro.h"
#include "Cutton.h"
#include "CharactorSelect.h"
#include "myResourceManager.h"
#include "myCamera.h"
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
		input_Sound
			= ResourceManager::Load<Sound>(L"input_Sound", L"..\\Resources\\Sound\\sfx_sounds_pause7_in.wav");

		object::Instantiate<Intro>(Vector2::Zero, eLayerType::BACKGROUND);
		//object::Instantiate<Cutton>(Vector2(-1,-1), eLayerType::UI);
	}
	void IntroScene::Update()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::LBUTTON; i++)
		{
        	if (Input::GetKeyState((eKeyCode)i) == eKeyState::Down)
			{
				input_Sound->Play(false);
				SceneManager::LoadScene(eSceneType::Title); // 바로 화면 전환
			}
		}

		Vector2 mPos = Input::GetMousePos();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (mPos.x > 3 && mPos.x < 1277 && mPos.y > 3 && mPos.y < 710)
			{
				input_Sound->Play(false);
				SceneManager::LoadScene(eSceneType::Title); // 바로 화면 전환
			}
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
		Sound* mainTheme
			= ResourceManager::Load<Sound>(L"MainTheme", L"..\\Resources\\Sound\\sfx_titleIntro.wav");

		mainTheme->Play(false);
	}
	void IntroScene::OnExit()
	{

	}
}