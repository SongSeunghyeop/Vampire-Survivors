#pragma once
#include "Enemy.h"


namespace my
{
	class Level_Item : public Enemy
	{
	public:

		Level_Item();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void onCollisionEnter(class Collider* other) override;
		virtual void onCollisionExit(class Collider* other) override;
		virtual void onCollisionStay(class Collider* other) override;

	private:
		Collider* Item_Collider;
		Image* Item_Image;
		Transform* Item_TR;
	};
}