#pragma once
#include "myComponent.h"
#include "myAnimation.h"
#include "myImage.h"

namespace my
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			//void(*name)(int, int);
			std::function<void()> mEvent;
		};

		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;

			//mStartEvent();
			//mStartEvent = test;
		};

		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		//�ϼ��� ��������Ʈ ��Ʈ�� �����ؼ� �ִϸ��̼� �����ϴ� �Լ�
		void CreateAnimation(const std::wstring& name
			, Image* sheet
			, Vector2 leftTop
			, UINT coulmn, UINT row, UINT spriteLength
			, float duration, int r, int g, int b);

		// ������ ����ִ� ��������Ʈ���� �̿��ؼ� �ִϸ��̼� �������ִ� �Լ�
		void CreateAnimations(const std::wstring& path, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool loop);
		void Play_NO_RE(const std::wstring& name, bool loop);

		Events* FindEvents(const std::wstring& name);

		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
		bool IsComplete() { return activeAnimation->IsComplete(); }


		Animation* getActiveAnmation() { return activeAnimation; }
		
	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;

		Animation* activeAnimation;
		Image* mSpriteSheet;
		bool mbLoop;
	};
}
