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
	class Book_Shadow;

	class Book : public GameObject
	{
	public:
		Book();
		~Book();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void onCollisionEnter(Collider* other);
		void onCollisionStay(Collider* other);
		void onCollisionExit(Collider* other);

		void setR(int r) { R = r; }
	private:
		Vector2 bookPos;
		Vector2 EnemyPos;

		float R;
		float mTime;
		float effect_Time;
		float bullet_vel;

		Image* book_Image;

		Animator* Ax_Animator;

		Vector2 dir;
		Vector2 rotation;

		Book_Shadow* shadow;
	};
}
