#pragma once
#include "myGameObject.h"
#include "myResourceManager.h"
#include "myTransform.h"
#include "myImage.h"
#include "myCollider.h"

namespace my
{
	class DragonBullet : public GameObject
	{
	public:
		DragonBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Vector2 bulletPos;

		float mTime;
		float bullet_vel;
		Image* bullet_Image;
	};
}
