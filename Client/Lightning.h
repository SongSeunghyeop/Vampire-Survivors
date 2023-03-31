#pragma once
#include "Krochi.h"

namespace my
{
	class Lightning : public GameObject
	{
	public:
		Lightning();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void skill_CompleteEvent();
		Collider* lightning_Collider;

	private:

		Image* lightning;

		Transform* lightning_Tr;
		Animator* lightning_Animation;

		Vector2 lightning_Pos;
	};
}
