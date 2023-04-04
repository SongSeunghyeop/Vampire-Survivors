#pragma once
#include "myGameObject.h"
#include "myImage.h"
#include "myTransform.h"
#include "myResourceManager.h"
#include "myCollider.h"
#include "myAnimator.h"

namespace my
{
	class Treasure_UI : public GameObject
	{
	public:

		Treasure();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void onCollisionEnter(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionStay(class Collider* other) override;

	private:
		Collider* Item_Collider;
		Image* option;
		Transform* Item_TR;
		Animator* Treasure_show;
	};
}