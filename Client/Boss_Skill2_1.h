#pragma once
#include "Boss.h"

namespace my
{
	class Boss_Skill2_1 : public GameObject
	{
	public:
		Boss_Skill2_1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		Collider* Ice_Collider;
		Vector2 getSkillPos() { return Ice_Pos; }
	private:
		Image* Ice;
		float mTime = 0.0f;
		Transform* Ice_Tr;
		Animator* Ice_Animation;
		Vector2 Ice_Pos;

		bool R;
	};
}
