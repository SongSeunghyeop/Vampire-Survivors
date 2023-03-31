#include "myResourceManager.h"
#include "Enemy.h"
#include "Time.h"
#include "Effect.h"
#include "myObject.h"
#include "Level_Item.h"

namespace my
{
	bool Enemy::Finded;

	Enemy::Enemy()
	{
		Entity::setName(L"Enemy");
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::Initialize()
	{
		EnemyR_Img = ResourceManager::Load<Image>(L"EnemyR", L"..\\Resources\\Fly_R_All.bmp");
		EnemyL_Img = ResourceManager::Load<Image>(L"EnemyL", L"..\\Resources\\Fly_L_All.bmp");
		Damaged_R = ResourceManager::Load<Image>(L"Damaged_R", L"..\\Resources\\Damaged_R.bmp");
		Damaged_L = ResourceManager::Load<Image>(L"Damaged_L", L"..\\Resources\\Damaged_L.bmp");
		Die_R = ResourceManager::Load<Image>(L"fly_Die_R", L"..\\Resources\\fly_Die_R.bmp");
		Die_L = ResourceManager::Load<Image>(L"fly_Die_L", L"..\\Resources\\fly_Die_L.bmp");
		//
		Zombie_R = ResourceManager::Load<Image>(L"Zombie_R", L"..\\Resources\\Zombie_Move_R.bmp");
		Zombie_L = ResourceManager::Load<Image>(L"Zombie_L", L"..\\Resources\\Zombie_Move_L.bmp");
		Zombie_Die_R = ResourceManager::Load<Image>(L"Zombie_Die_R", L"..\\Resources\\Zombie_Die_R.bmp");
		Zombie_Die_L = ResourceManager::Load<Image>(L"Zombie_Die_L", L"..\\Resources\\Zombie_Die_L.bmp");



		// ----- Black_Fly
		EnemyAnimator = AddComponent<Animator>();
		EnemyAnimator->CreateAnimation(L"RightWalk", EnemyR_Img, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"LeftWalk", EnemyL_Img, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Idle_R", EnemyL_Img, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Idle_L", EnemyL_Img, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Damaged_R", Damaged_R, Vector2::Zero, 2, 1, 2, 0.1f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Damaged_L", Damaged_L, Vector2::Zero, 2, 1, 2, 0.1f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"fly_Die_R", Die_R, Vector2::Zero, 3, 1, 3, 0.12f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"fly_Die_L", Die_L, Vector2::Zero, 3, 1, 3, 0.12f, 255, 0, 255);
		//
		// ----- Zombie
		EnemyAnimator->CreateAnimation(L"Zombie_MoveR", Zombie_R, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Zombie_MoveL", Zombie_L, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Zombie_IdleR", Zombie_R, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Zombie_IdleL", Zombie_L, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Zombie_DieR", Zombie_Die_R, Vector2::Zero, 3, 1, 3, 0.12f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Zombie_DieL", Zombie_Die_L, Vector2::Zero, 3, 1, 3, 0.12f, 255, 0, 255);
		//
		EnemyPos = GetComponent<Transform>();
		EnemyCollider = AddComponent<Collider>();
		EnemyCollider->setRGB(0, 255, 0);

		//랜덤 타입
		int TypeNum = rand() % 10; // 0 ~ 9

		if (TypeNum < 4) //0 ~ 3
			eType = eEnemyType::ZOMBIE;

		else // 4 ~ 9
			eType = eEnemyType::BLACK;

		if (TypeNum > 0 && TypeNum < 8) // 70%
			Finded = true;
		//

		// 타입에 따른 생성 정보
		switch (eType)
		{
		case(eEnemyType::BLACK):
		{
			EnemyAnimator->Play(L"RightWalk", true);
			monster_hp = 160;
			Enemy_vel = 70.0f;
			EnemyPos->setScale(Vector2(2.4f, 2.4f));
			EnemyCollider->setCenter(Vector2(-7, -10));
			EnemyCollider->setSize(Vector2(50, 28)); // 50,28
		}
			break;
		case(eEnemyType::ZOMBIE):
		{
			EnemyAnimator->Play(L"Zombie_MoveR", true);
			monster_hp = 160;
			Enemy_vel = 90.0f;
			EnemyPos->setScale(Vector2(2.0f, 2.0f));
			EnemyCollider->setCenter(Vector2(-12, -30));
			EnemyCollider->setSize(Vector2(54, 65)); // 50,70
		}
			break;
		}
		//
		eState = eEnemyState::Move;

		GameObject::Initialize();
	}
	void Enemy::Update()
	{
		EnemyPos = GetComponent<Transform>();
		Ppos.x = Krochi::getPlayerPos().x;
		Ppos.y = Krochi::getPlayerPos().y;
		EnemyCollider->setRGB(0, 255, 0);
		movePos = EnemyPos->getPos();

		if (monster_hp <= 0)
			eState = eEnemyState::Death;

		switch (eState)
		{
		case (eEnemyState::Move):
			Move();
			break;
		case (eEnemyState::Back_Move):
			Back_Move();
			break;
		case (eEnemyState::Death):
			Death();
			break;
		case(eEnemyState::None):
			None();
			break;
		}

		EnemyPos->setPos(movePos);

		GameObject::Update();
	}
	void Enemy::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Enemy::Release()
	{
		GameObject::Release();
	}

	void Enemy::Move()
	{
		if (Enemy::Finded)
		{
			if (Ppos.x > movePos.x)
			{ 
				movePos.x += Enemy_vel * Time::getDeltaTime();

				if(eType == eEnemyType::BLACK)
					EnemyAnimator->Play_NO_RE(L"RightWalk", true);
				if(eType == eEnemyType::ZOMBIE)
					EnemyAnimator->Play_NO_RE(L"Zombie_MoveR", true);
			}
			if (Ppos.x < movePos.x)
			{
				movePos.x -= Enemy_vel * Time::getDeltaTime();

				if (eType == eEnemyType::BLACK)
					EnemyAnimator->Play_NO_RE(L"LeftWalk", true);

				if (eType == eEnemyType::ZOMBIE)
					EnemyAnimator->Play_NO_RE(L"Zombie_MoveL", true);
			}
			if (Ppos.y > movePos.y)
			{
				movePos.y += Enemy_vel * Time::getDeltaTime();
			}
			if (Ppos.y < movePos.y)
			{
				movePos.y -= Enemy_vel * Time::getDeltaTime();
			}
		}

		if (!Enemy::Finded)
		{
			Distance = 
				std::abs(Ppos.x - movePos.x) + std::abs(Ppos.y - movePos.y);

			if (Distance > 3000) // 플레이어와의 거리가 멀어진다면, 위치를 가까이 옮겨줌
				EnemyPos->setPos(Krochi::getPlayerPos() + Init_Pos);
		}
	}

	void Enemy::Back_Move()
	{
		delay += Time::getDeltaTime();

		if (delay >= 0.3f)
		{
			delay = 0.0f;
			eState = eEnemyState::Move;
		}
	
		float vel = 9.0f;

		if (Ppos.y < movePos.y)
			movePos.y += vel * Time::getDeltaTime();
		if (Ppos.x > movePos.x)
			movePos.x -= vel * Time::getDeltaTime();
		if (Ppos.x < movePos.x)
			movePos.x += vel * Time::getDeltaTime();
		if (Ppos.y > movePos.y)
			movePos.y  -= vel * Time::getDeltaTime();
	}

	void Enemy::Death()
	{
		if (Ppos.x > movePos.x)
		{
		if (eType == eEnemyType::BLACK)
			EnemyAnimator->Play_NO_RE(L"fly_Die_R", false);
		if (eType == eEnemyType::ZOMBIE)
			EnemyAnimator->Play_NO_RE(L"Zombie_DieR", false);
		}
		if (Ppos.x < movePos.x)
		{
		if (eType == eEnemyType::BLACK)
			EnemyAnimator->Play_NO_RE(L"fly_Die_L", false);
		if (eType == eEnemyType::ZOMBIE)
			EnemyAnimator->Play_NO_RE(L"Zombie_DieL", false);
		}
	
		if (EnemyAnimator->IsComplete())
		{
			lv_Item = object::Instantiate<Level_Item>
				(EnemyPos->getPos(), eLayerType::ITEMS);
			object::Destory(this);
		}
	}

	void Enemy::onCollisionStay(Collider* other)
	{
		if (other->getOwner()->getName() == L"Radar")
		{
			Enemy::Finded = true;
		}
		if (other->getOwner()->getName() == L"Enemy")
		{
			EnemyCollider->setRGB(255, 0, 0);
			otherEnemy = dynamic_cast<Enemy*>(other->getOwner());

			if (otherEnemy->Distance < this->Distance)
				this->eState = eEnemyState::Back_Move;
			else
				this->eState = eEnemyState::Move;
		}
		if (other->getOwner()->getName() == L"Skill")
		{
			eState = eEnemyState::Back_Move;
			EnemyCollider->setRGB(255, 0, 0);
			if (other->getOwner()->getState() == GameObject::eState::Death)
			{
				monster_hp -= Krochi::getPlayerPower();

				mEffect = object::Instantiate<Effect>
					(EnemyPos->getPos() + Vector2(3.0f, 0.0f), eLayerType::EFFECT);
			}
		}
	}
	void Enemy::onCollisionExit(Collider* other)
	{
		if (other->getOwner()->getName() == L"Radar")
		{
			Enemy::Finded = false;
		}
	}
}