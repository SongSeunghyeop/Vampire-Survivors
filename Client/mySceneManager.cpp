#include "mySceneManager.h"
#include "myIntroScene.h"
#include "myTitleScene.h"
#include "myToolScene.h"
#include "InGameUI.h"
#include "myPlayScene.h"
#include "myEndingScene.h"
namespace my 
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::activeScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::Max); // �Ҵ��� ���ְ� ��ü�� 0���� �ʱ�ȭ���ش� �������, resize(5,0)�̸� 5���� �迭�� 0���� �ʱ�ȭ
																			 // ���� max�� 4���̹Ƿ� 4���� �迭�� 0���� �ʱ�ȭ
 		mScenes[(UINT)eSceneType::Intro] = new IntroScene(); 
		mScenes[(UINT)eSceneType::Title] = new TitleScene(); 
		mScenes[(UINT)eSceneType::Play] = new PlayScene(); 
		mScenes[(UINT)eSceneType::Option] = new Option(); 
		mScenes[(UINT)eSceneType::Tool] = new ToolScene();
		mScenes[(UINT)eSceneType::Ending] = new EndingScene();

		mScenes[(UINT)eSceneType::Intro]->setName(L"INTRO");
		mScenes[(UINT)eSceneType::Title]->setName(L"TITLE");
		mScenes[(UINT)eSceneType::Play]->setName(L"PLAY");
		mScenes[(UINT)eSceneType::Option]->setName(L"OPTION");
		mScenes[(UINT)eSceneType::Tool]->setName(L"TOOL");
		mScenes[(UINT)eSceneType::Ending]->setName(L"ENDING");

		for (Scene* scene : mScenes)
		{
			if (scene == NULL) continue;

			activeScene = scene;
			scene->Initialize();
 		}

		activeScene = mScenes[(UINT)eSceneType::Intro];
	}

	void SceneManager::Update()
	{	
		activeScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		activeScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == NULL) continue;

			scene->Release();
			delete scene;
			scene = NULL;
		}
	}
	void SceneManager::Destroy()
	{
  		activeScene->Destroy();
	}
	void SceneManager::LoadScene(eSceneType type) // ������Ʈ,�������� ����� �ٲپ���
	{
		Camera::Clear();
		// �����
		activeScene->OnExit();

		CollisionManager::clear();
		//������
		activeScene = mScenes[(UINT)type];
		activeScene->OnEnter();
	}
}
