#include "myCamera.h"
#include "myApplication.h"
#include "myGameObject.h"
#include "myTransform.h"
#include "myInput.h"
#include "Time.h"
#include "myImage.h"

extern my::Application myapplication;

namespace my
{

	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	Camera::eCameraEffectType Camera::mType = Camera::eCameraEffectType::None;
	class Image* Camera::mCutton = nullptr;
	float Camera::mCuttonAlpha = 1.0f;
	float Camera::mAlphaTime = 0.0f;
	float Camera::mEndTime = 5.0f;

	void Camera::Initiailize()
	{
		mResolution.x = myapplication.GetWidth();
		mResolution.y = myapplication.GetHeight();
		mLookPosition = (mResolution / 2.0f);

		mType = eCameraEffectType::None;
		mCutton = Image::Create(L"Cutton", mResolution.x, mResolution.y);
	}

	void Camera::Update()
	{
		if (mTarget != nullptr)
		{
			mLookPosition
				= mTarget->GetComponent<Transform>()->getPos() + Vector2(10,10);
		}


		if (mAlphaTime < mEndTime)
		{
			//255 - > 1
			mAlphaTime += Time::getDeltaTime();
			float ratio = (mAlphaTime / mEndTime);

			if (mType == eCameraEffectType::FadeIn)
			{
				mCuttonAlpha = 1.0f - ratio;
			}
			else if (mType == eCameraEffectType::FadeOut)
			{
				mCuttonAlpha = ratio;
			}
			else
			{

			}
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Render(HDC hdc)
	{
		if (mAlphaTime < mEndTime
			&& mType == eCameraEffectType::FadeIn)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;
			func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

			AlphaBlend(hdc, 0, 0
				, mResolution.x, mResolution.y
				, mCutton->GetHdc()
				, 0, 0
				, mCutton->GetWidth(), mCutton->GetHeight()
				, func);
		}
	}

	void Camera::Clear()
	{
		mResolution.x = myapplication.GetWidth();
		mResolution.y = myapplication.GetHeight();
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
	}
}
