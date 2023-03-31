#include "myScene.h"

namespace my
{
	Scene::Scene()
	{
		mLayers.resize((UINT)eLayerType::END);
	}
	Scene::~Scene()
	{
	
	}

	void Scene::Initialize()
	{

	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
 		}
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}

	void Scene::Destroy()
	{
		std::vector<GameObject*> deleteGameObjects = {};
		for (Layer& layer : mLayers)
		{
 			std::vector<GameObject*>& gameObjects
				= layer.GetGameObjects();

			for (std::vector<GameObject*>::iterator iter = gameObjects.begin()
				; iter != gameObjects.end(); )
			{
				if ((*iter)->getState() == GameObject::eState::Death)
				{
					deleteGameObjects.push_back((*iter));
					iter = gameObjects.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}

		for (GameObject* deathObj : deleteGameObjects)
		{
			delete deathObj;
			deathObj = NULL;
		}
	}

	void Scene::Release()
	{
		for (Layer& layer : mLayers)
		{
			layer.Release();

		}
	}

	void Scene::OnEnter()
	{

	}
	void Scene::OnExit()
	{
	
	}

	void Scene::AddGameObj(GameObject* obj, eLayerType layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);
	}
	std::vector<GameObject*>& Scene::GetGameObj(eLayerType layer)
	{
		return mLayers[(UINT)layer].GetGameObjects();
	}
}
