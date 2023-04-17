#pragma once
#include "myGameObject.h"
#include "myResourceManager.h"
#include "myTransform.h"
#include "myInput.h"
#include "myImage.h"
#include "myCollider.h"
#include "myAnimator.h"

namespace my
{
	class Cross : public GameObject
	{
	public:
		Cross();
		~Cross();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void onCollisionEnter(Collider* other);
		void onCollisionStay(Collider* other);
		void onCollisionExit(Collider* other);

		void setR(int r) { R = r; }
		void setCrossScale(float f) { cross_scale = f; }

	private:
		float mTime;
		float bullet_vel;

		Vector2 bulletPos;
		Vector2 EnemyPos;

		int R;
		float effect_Time;
		float cross_scale;
		Image* ax_Image;

		Animator* Ax_Animator;

		Vector2 dir;
		Vector2 rotation;
	};
}
