#include "Boss.h"
#include "Boss_Skill.h"
#include "Boss_Skill2.h"
#include "Boss_Hp.h"
#include "Boss_After.h"
#include "myObject.h"
#include "Time.h"
#include "PlaySceneManager.h"
#include "EnemyManager.h"

namespace my
{
	Vector2 Boss::movePos;

	Boss::Boss()
	{
		Entity::setName(L"Enemy");
	}
	Boss::~Boss()
	{

	}

	void Boss::Initialize()
	{
		Boss_R = ResourceManager::Load<Image>(L"Boss_R", L"..\\Resources\\Boss_R.bmp");
		Boss_L = ResourceManager::Load<Image>(L"Boss_L", L"..\\Resources\\Boss_L.bmp");
		bDamaged_R = ResourceManager::Load<Image>(L"bDamaged_R", L"..\\Resources\\Boss_Damaged_R.bmp");
		bDamaged_L = ResourceManager::Load<Image>(L"bDamaged_L", L"..\\Resources\\Boss_Damaged_L.bmp");

		boss_Animator = AddComponent<Animator>();
		boss_Animator ->CreateAnimation(L"Boss_MoveR", Boss_R, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);
		boss_Animator ->CreateAnimation(L"Boss_MoveL", Boss_L, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);

		boss_Animator ->CreateAnimation(L"Boss_IdleR", Boss_R, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);
		boss_Animator ->CreateAnimation(L"Boss_IdleL", Boss_L, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);

		boss_Animator ->CreateAnimation(L"bDamaged_R", bDamaged_R, Vector2::Zero, 1, 1, 1, 0.15f, 255, 0, 255);
		boss_Animator ->CreateAnimation(L"bDamaged_L", bDamaged_L, Vector2::Zero, 1, 1, 1, 0.15f, 255, 0, 255);

		boss_Tr = GetComponent<Transform>();
		boss_Tr->setScale(Vector2(4.0f, 4.0f));

		boss_Collider = AddComponent<Collider>();
		boss_Collider->setRGB(0, 255, 0);
		boss_Collider->setCenter(Vector2(0, -20));
		boss_Collider->setSize(Vector2(120, 150));

		boss_Animator->Play(L"Boss_MoveL", true);
		boss_hp = 160;
		Boss_vel = 360.0f;
		//
		eState = eBossState::Idle;

		hp = object::Instantiate<Boss_Hp>(eLayerType::ENEMYAFTER);
		hp->SetBoss(this);
		GameObject::Initialize();
	}
	void Boss::Update()
	{
		skill_Time += Time::getDeltaTime();
		boss_Collider->setRGB(0, 255, 0);
		boss_Tr = GetComponent<Transform>();
		Ppos = Krochi::getPlayerPos();
		movePos = boss_Tr->getPos();

		switch (eState)
		{
		case (eBossState::Idle):
		{
			delay += Time::getDeltaTime();
			skill_Time = 0.0f;
			if (delay >= 6.0f)
			{
				delay = 0.0f;

				for (int i = 0; i < 4; i++)
				{
					Boss_After* shadow =
						object::Instantiate<Boss_After>(boss_Tr->getPos(), eLayerType::ENEMYAFTER);

					shadow->setShadowDistance(20.0f - i * 5);
				}

				eState = eBossState::Move;
			}
		}
			break;
		case (eBossState::Move):
			move();
			break;
		case (eBossState::Back_Move):
			back_move();
			break;
		case (eBossState::Attack):
		{
			int randnum = rand() % 2; // 0,1

			if(randnum == 0)
				attack_1();
			if (randnum == 1)
				attack_1();
		}
			break;
		}

		boss_Tr->setPos(movePos);

		if (skill_Time >= 10.0f)
			eState = eBossState::Attack;

		boss_hp += 1.0f * Time::getDeltaTime();

		GameObject::Update();
	}
	void Boss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Boss::Release()
	{
		GameObject::Release();
	}

	void Boss::attack_1()
	{
		Boss_Skill* m1
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(-280.0f, -500.0f), eLayerType::SKILL);
		Boss_Skill* m2
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(-200.0f, -500.0f), eLayerType::SKILL);
		Boss_Skill* m3
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(-120.0f,-450.0f), eLayerType::SKILL);
		Boss_Skill* m4
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(-40.0f, -400.0f), eLayerType::SKILL);
		Boss_Skill* m5
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(40.0f, -400.0f), eLayerType::SKILL);
		Boss_Skill* m6
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(120.0f, -450.0f), eLayerType::SKILL);
		Boss_Skill* m7
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(200.0f, -500.0f), eLayerType::SKILL);
		Boss_Skill* m8
			= object::Instantiate<Boss_Skill>(Krochi::getPlayerPos() + Vector2(280.0f, -500.0f), eLayerType::SKILL);
		
		eState = eBossState::Move;
		skill_Time = 0.0f;
	}
	void Boss::attack_2()
	{
		eState = eBossState::Move;
		skill_Time = 0.0f;
	}

	void Boss::move()
	{
		movePos += (Ppos - boss_Tr->getPos()).Normalize() * Boss_vel * Time::getDeltaTime();

		if (Ppos.x - 10 > movePos.x)
			boss_Animator->Play_NO_RE(L"Boss_MoveR", true);

		if (Ppos.x + 10 < movePos.x)
			boss_Animator->Play_NO_RE(L"Boss_MoveL", true);
	}

	void Boss::back_move()
	{
		delay += Time::getDeltaTime();

		if (Ppos.x - 10 > movePos.x)
			boss_Animator->Play_NO_RE(L"bDamaged_R", true);

		if (Ppos.x + 10 < movePos.x)
			boss_Animator->Play_NO_RE(L"bDamaged_L", true);

		if (delay >= 0.15f)
		{
			delay = 0.0f;

			eState = eBossState::Move;
		}
	}

	void Boss::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Book")
		{
			boss_Collider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(boss_Tr->getPos() + Vector2(20.0f, 0.0f), eLayerType::EFFECT);

			boss_hp -= Krochi::getPlayerPower(L"Book") / 300;
			this->eState = eBossState::Back_Move;
		}
		if (other->getOwner()->getName() == L"Ax1")
		{
			boss_Collider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(boss_Tr->getPos() + Vector2(20.0f, 0.0f), eLayerType::EFFECT);

			boss_hp -= Krochi::getPlayerPower(L"Ax1") / 300;
			this->eState = eBossState::Back_Move;
		}
		if (other->getOwner()->getName() == L"Cross")
		{
			boss_Collider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(boss_Tr->getPos() + Vector2(20.0f, 0.0f), eLayerType::EFFECT);
			boss_hp -= Krochi::getPlayerPower(L"Cross") / 300;
			this->eState = eBossState::Back_Move;
		}
		if (other->getOwner()->getName() == L"Lightning")
		{
			boss_Collider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(boss_Tr->getPos() + Vector2(20.0f, 0.0f), eLayerType::EFFECT);
			boss_hp -= Krochi::getPlayerPower(L"Lightning") / 300;
			this->eState = eBossState::Back_Move;
		}
	}

	void Boss::onCollisionStay(Collider* other)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			Boss_vel = 0.0f;
		}
	}

	void Boss::onCollisionExit(Collider* other)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			Boss_vel = 360.0f;
		}
	}
}