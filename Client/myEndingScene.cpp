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
		ending = ResourceManager::Load<Image>(L"EndingImage", L"..\\Resources\\EndingImage.bmp"); // 이미지의 키와 경로 정보를 받음

		gameover = object::Instantiate<GameOver>(eLayerType::UI);
	}

	void EndingScene::Update()
	{
		Scene::Update();
	}
	void EndingScene::Render(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 3;//

		AlphaBlend(hdc, -1, -1
			, 1281, 721
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
	
	}
	void EndingScene::OnExit()
	{

	}
}