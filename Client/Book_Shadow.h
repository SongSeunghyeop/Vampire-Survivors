#pragma once
#include "Book.h"

namespace my
{
	class Book_Shadow : public SkillManager
	{
	public:
		Book_Shadow();
		~Book_Shadow();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void setBook(Book* b) { book = b; }
	private:
		Image* shadow_Image;
		Animator* Shadow_Animator;
		Book* book;
	};
}

