#pragma once
#include "myGameObject.h"
#include "myImage.h"
#include "myTransform.h"
#include "myAnimation.h"
#include "myResourceManager.h"
#include "myCollider.h"
#include "myAnimator.h"
#include "Krochi.h"

namespace my
{
	class Magnet_Arrow;

	class Magnet : public GameObject
	{
	public:

		Magnet();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void onCollisionEnter(class Collider* other) override;

		Vector2 getMagnetPos() { return Item_TR->getPos(); }
	private:
		Collider* Item_Collider;
		Animator* magnet_Animator;
		Image* magnet;
		Transform* Item_TR;
		Magnet_Arrow* arrow;

		Vector2 magnetPos;

		bool magnet_Down;
		bool magnet_Up;
		bool magnet_Right;
		bool magnet_Left;

		friend class Magnet_Arrow;
	};
}