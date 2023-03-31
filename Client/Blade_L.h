#pragma once
#include "Krochi.h"

namespace my
{
	class Blade_L : public GameObject
	{
	public:
		Blade_L();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void skillL_CompleteEvent();
		Collider* Blade_Collider;

	private:
		Vector2 EnemyPos;
		Image* Skill_L;

		Transform* Blade_Tr;
		Animator* Blade_Animator;

		Vector2 Blade_Pos;
	};
}
