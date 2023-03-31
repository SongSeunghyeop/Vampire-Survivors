#include "myLayer.h"

namespace my
{
	Layer::Layer()
	{

  	}
	Layer::~Layer()
	{

	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->getState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Update();

		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->getState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Render(hdc);
		}
	}
	void Layer::Release()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Release();
			delete gameObj;
			gameObj = NULL;
		}
	}
	void Layer::AddGameObject(GameObject* gameObj)
	{
		if (gameObj == nullptr)
			return;

		mGameObjects.push_back(gameObj);
	}
}