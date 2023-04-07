#pragma once
#include "Book.h"

namespace my
{
	class Book_Shadow : public GameObject
	{
	public:
		Book_Shadow();
		~Book_Shadow();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void setPos(Vector2 pos) { shadowPos = pos; }
	
	private:
		Vector2 shadowPos;
		Vector2 EnemyPos;

		float R;
		float mTime;
		float effect_Time;
		float bullet_vel;

		Image* shadow_Image;

		Animator* Shadow_Animator;

		Vector2 dir;
		Vector2 rotation;
	};
}

