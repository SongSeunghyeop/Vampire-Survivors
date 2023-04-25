#pragma once
#include "Skillmanager.h"

namespace my
{
	class Book_Shadow;

	class Book : public SkillManager
	{
	public:
		Book();
		~Book();
		
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	private:
		Book_Shadow* shadow;

		friend class Book_Shadow;
	};
}
