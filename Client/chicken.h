#pragma once
#include "Enemy.h"

namespace my
{
	class Chicken : public GameObject
	{
	public:

		Chicken();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void onCollisionEnter(class Collider* other) override;

	private:
		Collider* Item_Collider;
		Image* Item_Image;
		Transform* Item_TR;
	};
}