#pragma once
#include "myEntity.h"
#include "myGameObject.h"

namespace my 
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void AddGameObject(GameObject* gameObj);

		std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }
	private:
		std::vector<GameObject*> mGameObjects;
	};
}
