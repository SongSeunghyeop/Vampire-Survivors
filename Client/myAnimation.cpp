#include "myAnimation.h"
#include "Time.h"
#include "myImage.h"
#include "myAnimator.h"
#include "myGameObject.h"
#include "myTransform.h"

namespace my
{
    Animation::Animation()
        : mAnimator(nullptr)
        , mSheetImage(nullptr)
        , mTime(0.0f)
        , mbComplete(false)
        , mSpriteIndex(0)
        , delRGB(0, 0, 0)
        , mAnimationName(L"")
    {

    }

    Animation::~Animation()
    {

    }

    void Animation::Initialize()
    {

    }

    void Animation::Update()
    {
        if (mbComplete == true)
            return;

        mTime += Time::getDeltaTime();
        if (mSpriteSheets[mSpriteIndex].duration < mTime)
        {
            mTime = 0.0f;

            if (mSpriteSheets.size() <= mSpriteIndex + 1)
            {
                mbComplete = true;
            }
            else
            {
                mSpriteIndex++;
            }
        }
    }

    void Animation::Render(HDC hdc)
    {
        Transform* tr = mAnimator->getOwner()->GetComponent<Transform>();
        Vector2 scale = tr->getScale();
        Vector2 pos = tr->getPos();

        pos = Camera::CaluatePos(pos);
        pos.x -= mSpriteSheets[mSpriteIndex].size.x / 2.0f;
        pos.y -= mSpriteSheets[mSpriteIndex].size.y;

        TransparentBlt(hdc, (int)pos.x, (int)pos.y
            , (int)mSpriteSheets[mSpriteIndex].size.x * scale.x
            , (int)mSpriteSheets[mSpriteIndex].size.y * scale.y
            , mSheetImage->GetHdc()
            , (int)mSpriteSheets[mSpriteIndex].leftTop.x, mSpriteSheets[mSpriteIndex].leftTop.y
            , (int)mSpriteSheets[mSpriteIndex].size.x, mSpriteSheets[mSpriteIndex].size.y,
            RGB(delRGB.r, delRGB.g, delRGB.b));
    }

    void Animation::Create(Image* sheet, Vector2 leftTop
        , UINT coulmn, UINT row, UINT spriteLength
        , float duration, int r, int g, int b)
    {
        mSheetImage = sheet;

        //UINT coulmn = mSheetImage->GetWidth() / size.x;
        Vector2 size = Vector2::One;//(2.0f,2.0f)
        size.x = mSheetImage->GetWidth() / (float)coulmn;
        size.y = mSheetImage->GetHeight() / (float)row;

        for (size_t i = 0; i < spriteLength; i++)
        {
            Sprite spriteInfo;

            spriteInfo.leftTop.x = leftTop.x + (size.x * i);
            spriteInfo.leftTop.y = leftTop.y;
            spriteInfo.size = size;
            spriteInfo.duration = duration;

            mSpriteSheets.push_back(spriteInfo);
        }

        delRGB.r = r;
        delRGB.g = g;
        delRGB.b = b;
    }

    void Animation::Reset()
    {
        mSpriteIndex = 0;
        mTime = 0.0f;
        mbComplete = false;
    }
}
