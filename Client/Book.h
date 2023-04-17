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

		void setR(int r) { R = r; }
		void setDistance(float d) { distance = d;}
		void setVel(float v) { book_vel = v; }
		void setTime(float t) { book_Time = t; }

	private:
		Vector2 bookPos;
		Vector2 EnemyPos;

		float R;
		float mTime;
		float effect_Time;
		float distance;
		float book_vel;
		float book_Time;

		Image* book_Image;

		Animator* Ax_Animator;

		Vector2 dir;
		Vector2 rotation;

		Book_Shadow* shadow;

		friend class Book_Shadow;
	};
}
