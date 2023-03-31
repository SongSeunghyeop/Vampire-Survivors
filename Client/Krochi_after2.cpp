#include "Krochi_after2.h"

#pragma comment(lib, "msimg32.lib")

namespace my
{
	Krochi_after2::Krochi_after2()
	{
		Right_after = Krochi::Right_Dir;
	}
	Krochi_after2::~Krochi_after2()
	{

	}
	void Krochi_after2::Initialize()
	{
		playerImg_RA1 = ResourceManager::Load<Image>(L"PlayerRA1", L"..\\Resources\\Player_RightAfter.bmp");
		playerImg_LA1 = ResourceManager::Load<Image>(L"PlayerLA1", L"..\\Resources\\Player_LeftAfter.bmp");
		playerImg_N = ResourceManager::Load<Image>(L"PlayerN", L"..\\Resources\\Player_None.bmp");
		Damaged_R = ResourceManager::Load<Image>(L"DamagedAfter_R", L"..\\Resources\\Coll_RightAfter.bmp");
		Damaged_L = ResourceManager::Load<Image>(L"DamagedAfter_L", L"..\\Resources\\Coll_LeftAfter.bmp");

		playerAnimator = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		playerAnimator->CreateAnimation(L"RightAfter", playerImg_RA1, Vector2::Zero, 3, 1, 3, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"LeftAfter", playerImg_LA1, Vector2::Zero, 3, 1, 3, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"None", playerImg_N, Vector2::Zero, 1, 1, 1, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"DamagedAfter_R", Damaged_R, Vector2::Zero, 3, 1, 3, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"DamagedAfter_L", Damaged_L, Vector2::Zero, 3, 1, 3, 0.3f, 255, 0, 255);

		Transform* tr = GetComponent<Transform>();
		tr->setPos(Krochi::Playerpos);
		tr->setScale(Vector2::One);

		after_State = Krochi::ePlayerState::Idle;

		GameObject::Initialize();
	}
	void Krochi_after2::Update()
	{
		if (after_State == Krochi::ePlayerState::Idle)
		{
			idle();
			delay = 0.0f;
		}
		if (after_State == Krochi::ePlayerState::Move)
		{
			move();
			delay = 0.0f;
		}

		GameObject::Update();
	}

	void Krochi_after2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Krochi_after2::Release()
	{
		GameObject::Release();
	}
	void Krochi_after2::idle()
	{
    	Transform* tr = GetComponent<Transform>();
		afterPos = tr->getPos();

		if (afterPos.x < Krochi::Playerpos.x - 0.5)
				afterPos.x += 200.0f * Time::getDeltaTime();

		if (afterPos.x > Krochi::Playerpos.x + 0.5)
				afterPos.x -= 200.0f * Time::getDeltaTime();

		if (afterPos.y < Krochi::Playerpos.y - 0.5)
				afterPos.y += 200.0f * Time::getDeltaTime();

		if (afterPos.y > Krochi::Playerpos.y + 0.5)
				afterPos.y -= 200.0f * Time::getDeltaTime();

		tr->setPos(afterPos);

		while (delay <= 0.1f)
		{
			delay += 0.4 * Time::getDeltaTime();
		}

		playerAnimator->Play_NO_RE(L"None", true);

		if (Krochi::mState == Krochi::ePlayerState::Move)
			after_State = Krochi::ePlayerState::Move;
	}

	void Krochi_after2::move()
	{
		Right_after = Krochi::Right_Dir;

		if (Right_after && !(Krochi::P_Damaged))
			playerAnimator->Play_NO_RE(L"RightAfter", true);

		if (!Right_after && !(Krochi::P_Damaged))
			playerAnimator->Play_NO_RE(L"LeftAfter", true);

		if (Right_after && (Krochi::P_Damaged))
			playerAnimator->Play_NO_RE(L"DamagedAfter_R", true);

		if (!Right_after && (Krochi::P_Damaged))
			playerAnimator->Play_NO_RE(L"DamagedAfter_L", true);


		Transform* tr = GetComponent<Transform>();

		while (delay <= 0.1f)
		{
			delay += 0.4 * Time::getDeltaTime();
		}

		if (afterPos.x < Krochi::Playerpos.x - 8)
		{
			if (Input::GetKey(eKeyCode::D))
				afterPos.x += 200.0f * Time::getDeltaTime();
			else
				afterPos.x = Krochi::Playerpos.x;
		}
		if (afterPos.x > Krochi::Playerpos.x + 8)
		{
			if (Input::GetKey(eKeyCode::A))
				afterPos.x -= 200.0f * Time::getDeltaTime();
			else
				afterPos.x = Krochi::Playerpos.x;
		}
		if (afterPos.y < Krochi::Playerpos.y - 8)
		{
			if (Input::GetKey(eKeyCode::S))
				afterPos.y += 200.0f * Time::getDeltaTime();
			else
				afterPos.y = Krochi::Playerpos.y;
		}
		if (afterPos.y > Krochi::Playerpos.y + 8)
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