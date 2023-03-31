#include "Krochi_after.h"

#pragma comment(lib, "msimg32.lib")

namespace my
{
	Krochi::ePlayerState my::Krochi::mState;
	bool Krochi::Right_Dir;

	Krochi_after::Krochi_after()
	{
		Right_after = Krochi::Right_Dir;
		Shadow_distance = 0;

	}
	Krochi_after::~Krochi_after()
	{

	}

	void Krochi_after::Initialize()
	{
		playerImg_RA1 = ResourceManager::Load<Image>(L"PlayerRA1", L"..\\Resources\\Player_RightAfter.bmp");
		playerImg_LA1 = ResourceManager::Load<Image>(L"PlayerLA1", L"..\\Resources\\Player_LeftAfter.bmp");
		playerImg_N = ResourceManager::Load<Image>(L"PlayerN", L"..\\Resources\\Player_None.bmp");
		Damaged_R = ResourceManager::Load<Image>(L"DamagedAfter_R", L"..\\Resources\\Coll_RightAfter.bmp");
		Damaged_L = ResourceManager::Load<Image>(L"DamagedAfter_L", L"..\\Resources\\Coll_LeftAfter.bmp");

		Shadow_Animator = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		Shadow_Animator->CreateAnimation(L"RightAfter", playerImg_RA1, Vector2::Zero, 3,1,3,  0.3f, 255, 0, 255);
		Shadow_Animator->CreateAnimation(L"LeftAfter", playerImg_LA1, Vector2::Zero, 3,1,3, 0.3f, 255, 0, 255);
		Shadow_Animator->CreateAnimation(L"None", playerImg_N, Vector2::Zero, 1,1,1, 0.3f, 255, 0, 255);
		Shadow_Animator->CreateAnimation(L"DamagedAfter_R", Damaged_R, Vector2::Zero, 3,1,3, 0.3f, 255, 0, 255);
		Shadow_Animator->CreateAnimation(L"DamagedAfter_L", Damaged_L, Vector2::Zero, 3,1,3, 0.3f, 255, 0, 255);

		After_Tr = GetComponent<Transform>();

		After_Tr->setScale(Vector2(2.1f, 1.8f));

		after_State = Krochi::ePlayerState::Idle;

		GameObject::Initialize();
	}
	void Krochi_after::Update()
	{
		switch (after_State)
		{
		case(Krochi::ePlayerState::Idle):
			idle();
			break;
		case(Krochi::ePlayerState::Move):
			move();
			break;
		}

		GameObject::Update();
	}

	void Krochi_after::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Krochi_after::Release()
	{
		GameObject::Release();
	}
	void Krochi_after::idle()
	{
		Shadow_Animator->Play_NO_RE(L"None", true);

		if (Krochi::mState == Krochi::ePlayerState::Move)
			after_State = Krochi::ePlayerState::Move;
	}

	void Krochi_after::move()
	{
		Right_after = Krochi::Right_Dir;

		if (Right_after && !(Krochi::P_Damaged))
			Shadow_Animator->Play_NO_RE(L"RightAfter", true);

		if (!Right_after && !(Krochi::P_Damaged))
			Shadow_Animator->Play_NO_RE(L"LeftAfter", true);

		if (Right_after && (Krochi::P_Damaged))
			Shadow_Animator->Play_NO_RE(L"DamagedAfter_R", true);

		if (!Right_after && (Krochi::P_Damaged))
			Shadow_Animator->Play_NO_RE(L"DamagedAfter_L", true);

		Transform* tr = GetComponent<Transform>();
		afterPos = After_Tr->getPos();

		if (afterPos.x < Krochi::Playerpos.x - Shadow_distance)
		{
			if (Input::GetKey(eKeyCode::D))
				afterPos.x += 200.0f * Time::getDeltaTime();
			else
				afterPos.x = Krochi::Playerpos.x;
		}
		if (afterPos.x > Krochi::Playerpos.x + Shadow_distance)
		{
			if (Input::GetKey(eKeyCode::A))
				afterPos.x -= 200.0f * Time::getDeltaTime();
			else
				afterPos.x = Krochi::Playerpos.x;
		}
		if (afterPos.y < Krochi::Playerpos.y - Shadow_distance)
		{
			if (Input::GetKey(eKeyCode::S))
				afterPos.y += 200.0f * Time::getDeltaTime();
			else
				afterPos.y = Krochi::Playerpos.y;
		}
		if (afterPos.y > Krochi::Playerpos.y + Shadow_distance)
		{
			if (Input::GetKey(eKeyCode::W))
				afterPos.y -= 200.0f * Time::getDeltaTime();
			else
				afterPos.y = Krochi::Playerpos.y;
		}

		tr->setPos(afterPos);

		if (Krochi::mState == Krochi::ePlayerState::Idle)
			after_State = Krochi::ePlayerState::Idle;
	}
}