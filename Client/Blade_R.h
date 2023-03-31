#pragma once
#include "Krochi.h"

namespace my
{
	class Blade_R : public GameObject
	{
	public:
		Blade_R();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void skillR_CompleteEvent();
		Collider* Blade_Collider;

	private:
		Vector2 EnemyPos;
		Image* Skill_R;

		Transform* Blade_Tr;
		Animator* Blade_Animator;

		Vector2 Blade_Pos;
	};
}
