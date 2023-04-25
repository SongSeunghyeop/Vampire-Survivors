#include "myPlayScene.h"
#include "myObject.h"

namespace my
{
	PlayScene::PlayScene()
	{
	
	}
	PlayScene::~PlayScene()
	{

	}
	void PlayScene::Initialize()
	{
		krochi = object::Instantiate<Krochi>(eLayerType::PLAYER);
		field = object::Instantiate<Field>(eLayerType::BACKGROUND);
		E_manager = object::Instantiate<EnemyManager>(eLayerType::BACKGROUND);
		I_manager = object::Instantiate<ItemManager>(eLayerType::UI);
		P_manager = object::Instantiate<PlaySceneManager>(eLayerType::UI);
	
		treasure_Sound
			= ResourceManager::Load<Sound>(L"treasure_sound", L"..\\Resources\\Sound\\sfx_treasure_1.wav");
		
		PlayScene_Sound
			= ResourceManager::Load<Sound>(L"PlayScene_Sound", L"..\\Resources\\Sound\\bgm_vica_01.wav");
		Camera::SetTarget(krochi);
	}

	void PlayScene::Update()
	{
		//treasure_Sound->Play(false);
		if (Input::GetKeyState(eKeyCode::ESC) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Option);
			Input::SetKeyState(eKeyCode::ESC, eKeyState::None);
		}

		if (PlaySceneManager::Show_on)
		{
			PlayScene_Sound->Stop(true);
		}
		if (!PlaySceneManager::Show_on && PlayScene_Sound->stoped)
		{
			PlayScene_Sound->Play(true);
		}
		if (Krochi::getPlayerState() == Krochi::ePlayerState::Death)
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}
		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayScene::Release()
	{
		Scene::Release();
	}
	void PlayScene::OnEnter()
	{
		PlayScene_Sound->Play(false);

		CollisionManager::setLayer(eLayerType::PLAYER, eLayerType::ENEMY, true);
		CollisionManager::setLayer(eLayerType::PLAYER, eLayerType::SKILL, true);
		CollisionManager::setLayer(eLayerType::ENEMY, eLayerType::SKILL, true);
		CollisionManager::setLayer(eLayerType::ENEMY, eLayerType::ENEMY, true);
		CollisionManager::setLayer(eLayerType::PLAYER, eLayerType::ITEMS, true);
		CollisionManager::setLayer(eLayerType::RADAR, eLayerType::ENEMY, true);
		CollisionManager::setLayer(eLayerType::RADAR, eLayerType::SKILL, true);
	}
	void PlayScene::OnExit()
	{

	}
}