#pragma once
#include "myGameObject.h"
#include "myResourceManager.h"
#include "myInput.h"
#include "myImage.h"
#include "myCollider.h"

namespace my
{
	class BaseBullet : public GameObject
	{
	public:
		BaseBullet();
		~BaseBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void onCollisionEnter(Collider* other);
		void onCollisionStay(Collider* other);
		void onCollisionExit(Collider* other);
	private:
		Vector2 bulletPos;
		Vector2 EnemyPos;

		int R;
		bool BulletColl;
		float mTime;
		float effect_Time;

		Image* Bullet;
		Image* D_effect;
	};
}
