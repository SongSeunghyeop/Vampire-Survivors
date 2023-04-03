#include "myAnimator.h"
#include "myGameObject.h"
#include "myResourceManager.h"

namespace my
{
	Animator::Animator()
		: Component(eComponentType::ANIMATOR)
		, activeAnimation(nullptr)
		, mSpriteSheet(nullptr)
		, mbLoop(false)
	{

	}
	Animator::~Animator()
	{
		for (auto animation : mAnimations)
		{
			delete animation.second;
			animation.second = nullptr;
		}
		for (auto events : mEvents)
		{
			delete events.second;
			events.second = nullptr;
		}
	}

	void Animator::Initialize()
	{

	}
	void Animator::Update()
	{
		if (activeAnimation)
		{
			activeAnimation->Update();

			if (activeAnimation->IsComplete())
			{
				Animator::Events* events
					= FindEvents(activeAnimation->getAnimationName());

				if (events != nullptr)
					events->mCompleteEvent();
			}
			if (mbLoop && activeAnimation->IsComplete())
				activeAnimation->Reset();
		}
	}
	void Animator::Render(HDC hdc)
	{
		if (activeAnimation != NULL)
		{
			activeAnimation->Render(hdc);
		}
	}
	void Animator::Release()
	{

	}
	void Animator::CreateAnimation(const std::wstring& name
		, Image* sheet, Vector2 leftTop
		, UINT coulmn, UINT row, UINT spriteLength
		, float duration, int r, int g, int b)
	{
		Animation* animation = FindAnimation(name);

		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->Create(sheet, leftTop, coulmn, row, spriteLength, duration, r, g, b);
		animation->setAnimationName(name);
		animation->setAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
		Events* event = new Events();
		mEvents.insert(std::make_pair(name, event));
	}

	void Animator::CreateAnimations(const std::wstring& path, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Image*> images = {};
		for (const auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = path + L"\\" + fileName;

			const std::wstring ext = p.path().extension();
			if (ext == L".png")
				continue;

			Image* image = ResourceManager::Load<Image>(fileName, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
			{
				width = image->GetWidth() ;
			}
			if (height < image->GetHeight())
			{
				height = image->GetHeight();
			}
			fileCount++;
		}

		std::wstring key = fs.parent_path().filename();
		key += fs.filename();
		mSpriteSheet = Image::Create(key, width * fileCount, height);

		//
		int index = 0;
		for (Image* image : images)
		{
			int centerX = (width - image ->GetWidth()) / 2;
			int centerY = (height - image->GetHeight() );

			StretchBlt(mSpriteSheet->GetHdc()
				, width * index + centerX
				, 0 + centerY
				, image->GetWidth() , image->GetHeight() 
				, image->GetHdc(), 0, 0, image->GetWidth(), image->GetHeight(), SRCCOPY);

			index++;
		}

		CreateAnimation(key, mSpriteSheet, Vector2::Zero, index, 1, index, duration ,0,0,0);
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator it = mAnimations.find(name);

		if (it == mAnimations.end())
			return nullptr;

		return it->second;
	}
	void Animator::Play(const std::wstring& name, bool loop)
	{
		if (activeAnimation != NULL)
		{
			Animator::Events* prevEvents
				= FindEvents(activeAnimation->getAnimationName());

			if (prevEvents != NULL)
				prevEvents->mEndEvent();
		}

		activeAnimation = FindAnimation(name);
		activeAnimation->Reset();
		mbLoop = loop;

		Animator::Events* events
			= FindEvents(activeAnimation->getAnimationName());

		if (events != NULL)
			events->mStartEvent();

	}
	void Animator::Play_NO_RE(const std::wstring& name, bool loop)
	{
		//이벤트를 찾지 않는다, 리셋도 해주지 않는다, 액티브 애니메이션만 전환해준다

		if (name == L"NULL")
		{
			activeAnimation = NULL;
			return;
		}

		activeAnimation = FindAnimation(name);
		mbLoop = loop;
	}
	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

  		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Animator::Events* events
			= FindEvents(animation->getAnimationName());

		return events->mStartEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Animator::Events* events
			= FindEvents(animation->getAnimationName());

		return events->mCompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Animator::Events* events
			= FindEvents(animation->getAnimationName());

		return events->mEndEvent.mEvent;
	}
}