#include "myPlayScene.h"
#include "myObject.h"

namespace my
{
	float PlayScene::Play_Time;

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
		levelmanager = object::Instantiate<LevelManager>(eLayerType::UI);
		treasure = object::Instantiate<Treasure>(eLayerType::ITEMS);
		Play_Time = 0.0f;
		Camera::SetTarget(krochi);
	}

	void PlayScene::Update()
	{
		Play_Time += Time::getDeltaTime();

		if (Input::GetKeyState(eKeyCode::ESC) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Option);
			Input::SetKeyState(eKeyCode::ESC, eKeyState::None);
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
		CollisionManager::setLayer(eLayerType::PLAYER, eLayerType::ENEMY, true);
		CollisionManager::setLayer(eLayerType::ENEMY, eLayerType::SKILL, true);
		CollisionManager::setLayer(eLayerType::ENEMY, eLayerType::ENEMY, true);
		CollisionManager::setLayer(eLayerType::PLAYER, eLayerType::ITEMS, true);
		CollisionManager::setLayer(eLayerType::RADAR, eLayerType::ENEMY, true);
		//CollisionManager::setLayer(eLayerType::RADAR, eLayerType::ITEMS, true);
		CollisionManager::setLayer(eLayerType::RADAR, eLayerType::SKILL, true);
	}
	void PlayScene::OnExit()
	{

	}
}