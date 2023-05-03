#pragma once
#include "Boss.h"

namespace my
{
	class Boss_After : public Boss
	{
		enum class eAfterState
		{
			None,
			Move,
		};

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void move();
		void none() {};

		void setShadowDistance(float s) { shadow_distance = s; }
	private:
		eAfterState eState;

		Animator* BossAnimator;
		Transform* After_TR;
		Vector2 afterPos;
		Vector2 Ppos;

		Level_Item* lv_Item;
		//
		Image* Boss_R;
		Image* Boss_L;
		//
		float delay = 0.0f;
		float shadow_distance;
		float skill_Time = 0.0f;
		Vector2 Init_Pos;
	};
}

