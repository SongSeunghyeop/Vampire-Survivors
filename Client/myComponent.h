#pragma once
#include "myEntity.h"

namespace my 
{
	class GameObject;

	class Component : public Entity
	{
	public:

		Component(eComponentType Type);
	    ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		eComponentType getType() { return myType; }
		void setOwner(GameObject* owner) { myOwner = owner;  }
		GameObject* getOwner() { return myOwner; }


	private:
		const eComponentType myType;
		GameObject* myOwner;
	};
}
