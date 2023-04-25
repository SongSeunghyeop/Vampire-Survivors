#pragma once
#include "Skillmanager.h"

namespace my
{
	class Lightning : public SkillManager
	{
	public:
		Lightning();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void skill_CompleteEvent();

	private:
	};
}
