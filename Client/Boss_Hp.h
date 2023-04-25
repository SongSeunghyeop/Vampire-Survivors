#pragma once
#include "Boss.h"

namespace my
{
	class Boss_Hp : public Boss
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetBoss(Boss *b) { boss = b; }
	private:
		Image* hp_bar;
		Image* hp_bar2;
		Boss *boss;
	};
}

