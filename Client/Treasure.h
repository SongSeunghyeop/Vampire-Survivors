#pragma once
#include "myGameObject.h"
#include "myImage.h"
#include "myTransform.h"
#include "myResourceManager.h"
#include "myCollider.h"
#include "myAnimator.h"

namespace my
{
	class Treasure_Arrow;
	class Treasure : public GameObject
	{
	public:

		Treasure();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void onCollisionEnter(class Collider* other) override;
	
		Vector2 getTreasurePos() { return Item_TR->getPos(); }

		void setArrowDir();
	private:
		Collider* Item_Collider;
		Image* treasure;
		Transform* Item_TR;
		Treasure_Arrow* arrow;

		Vector2 treasurePos;
		bool treasure_down;
		bool treasure_up;
		bool treasure_Right;
		bool treasure_Left;

		friend class Treasure_Arrow;
	};
}