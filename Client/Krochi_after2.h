#pragma once
#include "Krochi.h"

namespace my
{
	class Krochi_after2 : public Krochi
	{
	public:

		Krochi_after2();
		~Krochi_after2();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		Animator* playerAnimator;
		Krochi::ePlayerState after_State;

		Image* playerImg_RA1;
		Image* playerImg_LA1;
		Image* playerImg_N;
		Image* Damaged_R;
		Image* Damaged_L;

		Vector2 afterPos;
		bool Right_after;
		float delay;

		void move();
		void idle();
	};
}

