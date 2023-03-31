#pragma once
#include "Krochi.h"

namespace my
{
	class Krochi_after : public Krochi
	{
	public:

		Krochi_after();
		~Krochi_after();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetShadow(int distance) { Shadow_distance = distance; }

	private:
		Animator* Shadow_Animator;
		Transform* After_Tr;
		Krochi::ePlayerState after_State;

		Image* playerImg_RA1;
		Image* playerImg_LA1;
		Image* playerImg_N;
		Image* Damaged_R;
		Image* Damaged_L;

		Vector2 afterPos;

		bool Right_after;
		float Shadow_distance;

		void move();
		void idle();
	};
}

