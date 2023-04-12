#pragma once
#include "myGameObject.h"
#include "myImage.h"
#include "myTransform.h"
#include "myResourceManager.h"
#include "myCollider.h"
#include "myAnimator.h"

namespace my
{
	class Treasure : public GameObject
	{
	public:

		Treasure();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void onCollisionEnter(class Collider* other) override;
	
		Vector2 getTreasurePos() { return Item_TR->getPos(); }
	private:
		Collider* Item_Collider;
		Image* treasure;
		Transform* Item_TR;
	};
}