#pragma once
#include "myEntity.h"
#include "myCamera.h"

namespace my
{
	class Image;
	class Animator;

	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

		Animation();
		~Animation();

		void Initialize();
		void Update();
		void Render(HDC hdc);
		void Create(Image* sheet, Vector2 leftTop, UINT coulmn, UINT row, UINT spriteLength, float duration, int r, int g, int b);
		void Reset();

		virtual bool IsComplete() { return mbComplete; }
		void setAnimator(Animator* animator) { mAnimator = animator; }
		void setAnimationName(std::wstring name) { mAnimationName = name; }
		std::wstring& getAnimationName() {return mAnimationName;}
	private:
		Animator* mAnimator;
		Image* mSheetImage;
		std::vector<Sprite> mSpriteSheets;
		MyRGB delRGB;

		float mTime;
		bool mbComplete;
		int mSpriteIndex;
		std::wstring mAnimationName;
	};
}
