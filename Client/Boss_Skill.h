#pragma once
#include "Krochi.h"

namespace my
{
	class Boss_Skill : public GameObject
	{
	public:
		Boss_Skill();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		Collider* meteor_Collider;

	private:

		Image* meteor;
		float mTime = 0.0f;
		Transform* meteor_Tr;
		Animator* meteor_Animation;
		Vector2 meteor_Pos;
	};
}
