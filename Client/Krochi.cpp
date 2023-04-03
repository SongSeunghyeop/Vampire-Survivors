#include "Krochi.h"

#include "Blade_L.h"
#include "Blade_R.h"
#include "Radar.h"
#include "Krochi_after.h"
#include "Lightning.h"
#include "LevelManager.h"

#pragma comment(lib, "msimg32.lib")

extern my::Application myapplication;

namespace my
{
	Vector2 Krochi::Playerpos = Vector2(100.f, 100.f);

	bool Krochi::P_Damaged;
	float Krochi::Hp;
	float Krochi::Exp;
	float Krochi::Monster_Exp;
	float Krochi::vel;
	float Krochi::Blade_Time;
	float Krochi::Light_Time;
	float Krochi::Power;
	int    Krochi::level;
	int    Krochi::Blade_Power;
	int    Krochi::Light_Power;

	Krochi::Krochi()
	{
		this->setName(L"Player");

		Krochi::Hp = 112.0f;
		Krochi::Exp = 0.0f; // max = 1126.0f
		Krochi::level = 1;
		Krochi::Monster_Exp = 250;
		Krochi::vel = 140.0f;
		Krochi::Blade_Time = 0.0f;
		Krochi::Light_Time = 0.0f;
		Krochi::Blade_Power = 40;
		Krochi::Light_Power = 90;
		Krochi::Power = 0;
	}
	Krochi::~Krochi()
	{

	}
	void Krochi::Initialize()
	{
		playerImg_R = ResourceManager::Load<Image>(L"PlayerR1", L"..\\Resources\\Player_RightRun.bmp");
		playerImg_L = ResourceManager::Load<Image>(L"PlayerL1", L"..\\Resources\\Player_LeftRun.bmp");
		damaged_R = ResourceManager::Load<Image>(L"damaged_R", L"..\\Resources\\Collision_RightRun.bmp");
		damaged_L = ResourceManager::Load<Image>(L"damaged_L", L"..\\Resources\\Collision_LeftRun.bmp");

 		playerAnimator = AddComponent<Animator>(); // 애니메이터 컴포넌트 배열에 동적할당 및 초기화
		playerAnimator->CreateAnimation(L"Idle_R", playerImg_R, Vector2::Zero, 3, 1, 1, 0.3f, 255, 0, 255); // 스프라이트 배열로 쪼개진 하나의 애니메이션 생성
  	 	playerAnimator->CreateAnimation(L"Idle_L", playerImg_L, Vector2::Zero, 3, 1, 1, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"RightRun", playerImg_R, Vector2::Zero, 3, 1, 3, 0.25f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"LeftRun", playerImg_L, Vector2::Zero, 3, 1, 3, 0.25f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"Damaged_IdleR", damaged_R, Vector2::Zero, 3, 1, 1, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"Damaged_IdleL", damaged_L, Vector2::Zero, 3, 1, 1, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"Damaged_RunR", damaged_R, Vector2::Zero, 3, 1, 3, 0.3f, 255, 0, 255);
		playerAnimator->CreateAnimation(L"Damaged_RunL", damaged_L, Vector2::Zero, 3, 1, 3, 0.3f, 255, 0, 255);

		playerAnimator->Play(L"Idle_R", true);

		Transform* tr = GetComponent<Transform>();
 		Krochi::Playerpos.x = myapplication.GetWidth() / 2 ;
 		Krochi::Playerpos.y = myapplication.GetHeight() / 2 ;
		tr->setPos(Krochi::Playerpos);
		tr->setScale(Vector2(2.1f,1.8f));

		Collider* collider = AddComponent<Collider>();
		collider->setCenter(Vector2(-13, -34));
		collider->setSize(Vector2(55, 61));

		radar = object::Instantiate<Radar>(Krochi::Playerpos, eLayerType::RADAR);
		after = object::Instantiate<Krochi_after>(Krochi::Playerpos, eLayerType::PLAYERAFTER);

		after->SetShadow(5);

		mState = ePlayerState::Idle;
		skillState = eSkillState::Blade;

		Right_Dir = true;


 		GameObject::Initialize();
	}
	void Krochi::Update()
	{
		radar->radar_Collider->setSize(radar->Radar_Size);

		switch (mState)
		{
		case my::Krochi::ePlayerState::Move:
			move();
			break;
		case my::Krochi::ePlayerState::Idle:
			idle();
			break;
		case  my::Krochi::ePlayerState::LevelUP:
			level_up();
			break;
		default:
			break;
		}
		switch (skillState)
		{
		case my::Krochi::eSkillState::Blade:
		{
			Blade();
			Light();
		}
			break;
		case my::Krochi::eSkillState::None:
			break;
		default:
			break;
		}
	
		GameObject::Update();
	}

	void Krochi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Krochi::Release()
	{
		GameObject::Release();
	}

	void Krochi::idle()
	{
		if (Right_Dir)
				playerAnimator->Play_NO_RE(L"Idle_R", true);
		if (!Right_Dir)
				playerAnimator->Play_NO_RE(L"Idle_L", true);

		if (Krochi::P_Damaged)
				Damaged(ePlayerState::Idle);

		for (int i = 0; i < 4; i++)
		{
			if (Input::GetKeyDown(eKeyCode(i)) || Input::GetKey(eKeyCode(i)))
			{
				mState = ePlayerState::Move;

				if(eKeyCode(i) == eKeyCode::A)
					Right_Dir = false;
				if (eKeyCode(i) == eKeyCode::D)
					Right_Dir = true;
			}
		}
	}

	void Krochi::move()
	{
		Transform* tr = GetComponent<Transform>();
		Playerpos = tr->getPos();

		if (Right_Dir)
			playerAnimator->Play_NO_RE(L"RightRun", true);

		if (!Right_Dir)
			playerAnimator->Play_NO_RE(L"LeftRun", true);

		if (Krochi::P_Damaged)
			Damaged(ePlayerState::Move);

		for (int i = 0; i < 4; i++)
		{
			if (Input::GetKeyUp(eKeyCode(i)))
			{
				mState = ePlayerState::Idle;

				if (eKeyCode(i) == eKeyCode::A)
					Right_Dir = false;
				if (eKeyCode(i) == eKeyCode::D)
					Right_Dir = true;
			}
		}

		if (Input::GetKey(eKeyCode::A) && Input::GetKey(eKeyCode::D))
		{
			mState = ePlayerState::Idle;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			Right_Dir = false;
			Playerpos.x -= vel * Time::getDeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Right_Dir = true;
			Playerpos.x += vel * Time::getDeltaTime();
		}
		if (Input::GetKey(eKeyCode::W))
		{
			Playerpos.y -= vel * Time::getDeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			Playerpos.y += vel * Time::getDeltaTime();
		}

		tr->setPos(Playerpos);
	}

	void Krochi::Damaged(ePlayerState state)
	{
		Hp -= Time::getDeltaTime() * 4.0f;

		if (state == ePlayerState::Idle)
		{
			if (Right_Dir)
				playerAnimator->Play_NO_RE(L"Damaged_IdleR", true);

			if (!Right_Dir)
				playerAnimator->Play_NO_RE(L"Damaged_IdleL", true);
		}
		if (state == ePlayerState::Move)
		{
			if (Right_Dir)
				playerAnimator->Play_NO_RE(L"Damaged_RunR", true);

			if (!Right_Dir)
				playerAnimator->Play_NO_RE(L"Damaged_RunL", true);
		}
	}

	void Krochi::level_up()
	{
		radar->radar_Collider->setSize(Vector2::Zero);

		LevelManager::Level_Up = true;
	}

	void Krochi::Blade()
	{
		if (Krochi::Blade_Time > 2.5f)
		{
			Krochi::Power = Krochi::Blade_Power;

			bladeR = object::Instantiate<Blade_R>(Krochi::Playerpos + Vector2(34.0f, -35.0f), eLayerType::SKILL);
			bladeL = object::Instantiate<Blade_L>(Krochi::Playerpos + Vector2(-110.0f, -35.0f), eLayerType::SKILL);
			Krochi::Blade_Time = 0.0f;
		}
	}
	void Krochi::Light()
	{
		if (Krochi::Light_Time > 4.0f)
		{
			Krochi::Power = Krochi::Light_Power;

			LightNum = 3;
			randNum = 0;
			
			EnemyNum = Radar::getEnemies().size();

			if (EnemyNum < LightNum)
				return;

			for (int i = 0; i < LightNum; i++)
			{
				while(EnemyIndex[randNum] == 1)
					randNum = rand() % EnemyNum;

				EnemyIndex[randNum] = 1;

				Lightning* light
					= object::Instantiate<Lightning>(Radar::getEnemies()[randNum]->getPos() + Vector2(16.0f, -174.0f), eLayerType::SKILL);
			}
			for (int i = 0; i < EnemyNum; i++)
			{
				if (EnemyIndex[i] > 0)
					EnemyIndex[i] = 0;
			}

			Krochi::Light_Time = 0.0f;
		}
	}

	void Krochi::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Level_Item")
		{
			Exp += Monster_Exp;

			if (Exp > 1126.0f)
			{
				Exp = -200.0f;
				Monster_Exp /= 1.3f;
				++Krochi::level;

				mState = ePlayerState::LevelUP;
			}
		}
	}											
	void Krochi::onCollisionStay(Collider* other)
	{
		Krochi::P_Damaged = true;
	}
	void Krochi::onCollisionExit(Collider* other)
	{
		Krochi::P_Damaged = false;
	}
}