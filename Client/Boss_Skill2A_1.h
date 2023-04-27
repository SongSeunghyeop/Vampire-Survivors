#pragma once
#include "Boss_Skill2_1.h"
namespace my
{
	class Boss_Skill2A_1 : public GameObject
	{
	public:
		Boss_Skill2A_1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		void setDistance(float d) { distance.x = d; distance.y = d; }
		void setSkill(Boss_Skill2_1* b) { skill = b; }
	private:
		Image* Ice;
		float mTime = 0.0f;
		Transform* Ice_Tr;
		Animator* Ice_Animation;
		Vector2 Ice_Pos;

		Vector2 distance;

		Boss_Skill2_1* skill;

		bool R;
	};
}
