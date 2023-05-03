#include "myEndingScene.h"
#include "GameOver.h"
#include "myObject.h"

namespace my
{
	EndingScene::EndingScene()
	{
		
	}
	EndingScene::~EndingScene()
	{

	}
	void EndingScene::Initialize()
	{
		ending = ResourceManager::Load<Image>(L"EndingImage", L"..\\Resources\\EndingImage.bmp"); // �̹����� Ű�� ��� ������ ����
		gameoversound
			= ResourceManager::Load<Sound>(L"gameoversound", L"..\\Resources\\Sound\\sfx_gameOver.wav");

		gameover = object::Instantiate<GameOver>(eLayerType::UI);
	}

	void EndingScene::Update()
	{
		if (gameover->go_back)
		{
			SceneManager::LoadScene(eSceneType::Intro);
			gameover->go_back = false;
		}

		Scene::Update();
	}
	void EndingScene::Render(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 3.0;//

		AlphaBlend(hdc, -1, -1
			, 1301, 801
			, ending->GetHdc()
			, 0, 0 
			, ending->GetWidth(), ending->GetHeight()
			, func);

		Scene::Render(hdc);
	}
	void EndingScene::Release()
	{
		Scene::Release();
	}
	void EndingScene::OnEnter()
	{
		gameoversound->Play(false);
	}
	void EndingScene::OnExit()
	{

	}
}