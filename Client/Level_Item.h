#pragma once
#include "Enemy.h"

namespace my
{
	class Level_Item : public GameObject
	{
	public:

		Level_Item();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void onCollisionEnter(class Collider* other) override;

		static float Item_vel;
	private:
		Collider* Item_Collider;
		Image* Item_Image;
		Transform* Item_TR;
		Vector2 Item_pos;
	};
}