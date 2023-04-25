#include "Enemy.h"
#include "myObject.h"
#include "Level_Item.h"
#include "chicken.h"
#include "PlaySceneManager.h"
#include "DragonBullet.h"
#include "EnemyManager.h"

namespace my
{
	bool Enemy::Finded;

	Enemy::Enemy()
	{
		Entity::setName(L"Enemy");
		vel_type1 = 130.0f; // 130
		vel_type2 = 150.0f;
		vel_type3 = 170.0f;
		vel_type4 = 190.0f;
	}

	void Enemy::Initialize()
	{
		//Type: Black
		EnemyR_Img = ResourceManager::Load<Image>(L"EnemyR", L"..\\Resources\\Fly_R_All.bmp");
		EnemyL_Img = ResourceManager::Load<Image>(L"EnemyL", L"..\\Resources\\Fly_L_All.bmp");
		Damaged_R = ResourceManager::Load<Image>(L"Damaged_R", L"..\\Resources\\Damaged_R.bmp");
		Damaged_L = ResourceManager::Load<Image>(L"Damaged_L", L"..\\Resources\\Damaged_L.bmp");
		Die_R = ResourceManager::Load<Image>(L"fly_Die_R", L"..\\Resources\\fly_Die_R.bmp");
		Die_L = ResourceManager::Load<Image>(L"fly_Die_L", L"..\\Resources\\fly_Die_L.bmp");
		//Type: Zombie
		Zombie_R = ResourceManager::Load<Image>(L"Zombie_R", L"..\\Resources\\Zombie_Move_R.bmp");
		Zombie_L = ResourceManager::Load<Image>(L"Zombie_L", L"..\\Resources\\Zombie_Move_L.bmp");
		zDamaged_R = ResourceManager::Load<Image>(L"zDamaged_R", L"..\\Resources\\Zombie_Damaged_R.bmp");
		zDamaged_L = ResourceManager::Load<Image>(L"zDamaged_L", L"..\\Resources\\Zombie_Damaged_L.bmp");
		Zombie_Die_R = ResourceManager::Load<Image>(L"Zombie_Die_R", L"..\\Resources\\Zombie_Die_R.bmp");
		Zombie_Die_L = ResourceManager::Load<Image>(L"Zombie_Die_L", L"..\\Resources\\Zombie_Die_L.bmp");
		//Type: Dragon
		Dragon_R = ResourceManager::Load<Image>(L"Dragon_R", L"..\\Resources\\Dragon_R.bmp");
		Dragon_L = ResourceManager::Load<Image>(L"Dragon_L", L"..\\Resources\\Dragon_L.bmp");
		dAttack_R = ResourceManager::Load<Image>(L"dAttack_R", L"..\\Resources\\Dragon_R.bmp");
		dAttack_L = ResourceManager::Load<Image>(L"dAttack_L", L"..\\Resources\\Dragon_L.bmp");
		dDamaged_R = ResourceManager::Load<Image>(L"dDamaged_R", L"..\\Resources\\dDamaged_R.bmp");
		dDamaged_L = ResourceManager::Load<Image>(L"dDamaged_L", L"..\\Resources\\dDamaged_L.bmp");
		//Type: Skull
		Skull_R = ResourceManager::Load<Image>(L"Skull_R", L"..\\Resources\\skull_R.bmp");
		Skull_L = ResourceManager::Load<Image>(L"Skull_L", L"..\\Resources\\skull_L.bmp");
		sDamaged_R = ResourceManager::Load<Image>(L"sDamaged_R", L"..\\Resources\\skull_Damaged_R.bmp");
		sDamaged_L = ResourceManager::Load<Image>(L"sDamaged_L", L"..\\Resources\\skull_Damaged_L.bmp");
		Skull_Die_R = ResourceManager::Load<Image>(L"Skull_Die_R", L"..\\Resources\\skull_Die_R.bmp");
		Skull_Die_L = ResourceManager::Load<Image>(L"Skull_Die_L", L"..\\Resources\\skull_Die_L.bmp");
		//Type: Ghost
		Ghost_R = ResourceManager::Load<Image>(L"Ghost_R", L"..\\Resources\\Ghost_R.bmp");
		Ghost_L = ResourceManager::Load<Image>(L"Ghost_L", L"..\\Resources\\Ghost_L.bmp");
		Ghost_Run_R = ResourceManager::Load<Image>(L"Ghost_Run_R", L"..\\Resources\\Ghost_Run_R.bmp");
		Ghost_Run_L = ResourceManager::Load<Image>(L"Ghost_Run_L", L"..\\Resources\\Ghost_Run_L.bmp");
		gDamaged_R = ResourceManager::Load<Image>(L"gDamaged_R", L"..\\Resources\\Ghost_Damaged_R.bmp");
		gDamaged_L = ResourceManager::Load<Image>(L"gDamaged_L", L"..\\Resources\\Ghost_Damaged_L.bmp");
		Ghost_DieR = ResourceManager::Load<Image>(L"Ghost_DieR", L"..\\Resources\\Ghost_Die_R.bmp");
		Ghost_DieL = ResourceManager::Load<Image>(L"Ghost_DieL", L"..\\Resources\\Ghost_Die_L.bmp");

		//Type: Candle
		candle = ResourceManager::Load<Image>(L"Candle", L"..\\Resources\\candle.bmp");
		EnemyAnimator = AddComponent<Animator>();
		// ----- Black_Fly
		EnemyAnimator->CreateAnimation(L"RightWalk", EnemyR_Img, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"LeftWalk", EnemyL_Img, Vector2::Zero, 2, 1, 2, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Idle_R", EnemyL_Img, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Idle_L", EnemyL_Img, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Damaged_R", Damaged_R, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Damaged_L", Damaged_L, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"fly_Die_R", Die_R, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"fly_Die_L", Die_L, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		//
		// ----- Zombie
		EnemyAnimator->CreateAnimation(L"Zombie_MoveR", Zombie_R, Vector2::Zero, 2, 1, 2, 0.45f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Zombie_MoveL", Zombie_L, Vector2::Zero, 2, 1, 2, 0.45f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Zombie_IdleR", Zombie_R, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Zombie_IdleL", Zombie_L, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"zDamaged_R", zDamaged_R, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"zDamaged_L", zDamaged_L, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Zombie_DieR", Zombie_Die_R, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Zombie_DieL", Zombie_Die_L, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		//
		// ----- Skull
		EnemyAnimator->CreateAnimation(L"Skull_MoveR", Skull_R, Vector2::Zero, 2, 1, 2, 0.4f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Skull_MoveL", Skull_L, Vector2::Zero, 2, 1, 2, 0.4f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Skull_IdleR", Skull_R, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Skull_IdleL", Skull_L, Vector2::Zero, 2, 1, 1, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"sDamaged_R", sDamaged_R, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"sDamaged_L", sDamaged_L, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Skull_DieR", Skull_Die_R, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Skull_DieL", Skull_Die_L, Vector2::Zero, 3, 1, 3, 0.1f, 255, 0, 255);
		// 
		//  ------ Dragon
		EnemyAnimator->CreateAnimation(L"Dragon_AttackR", Dragon_R, Vector2::Zero, 10, 1, 10, 0.4f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Dragon_AttackL", Dragon_L, Vector2::Zero, 10, 1, 10, 0.4f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Dragon_IdleR", Dragon_R, Vector2::Zero, 8, 1, 2, 0.4f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Dragon_IdleL", Dragon_L, Vector2::Zero, 8, 1, 2, 0.4f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"dDamaged_R", dDamaged_R, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"dDamaged_L", dDamaged_L, Vector2::Zero, 2, 1, 1, 0.15f, 255, 0, 255);

		EnemyAnimator->GetCompleteEvent(L"Dragon_AttackR") = std::bind(&Enemy::dskill_CompleteEvent, this);
		EnemyAnimator->GetCompleteEvent(L"Dragon_AttackL") = std::bind(&Enemy::dskill_CompleteEvent, this);
		//
		// -----Ghost
		EnemyAnimator->CreateAnimation(L"Ghost_R", Ghost_R, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Ghost_L", Ghost_L, Vector2::Zero, 1, 1, 1, 0.5f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Ghost_Run_R", Ghost_Run_R, Vector2::Zero, 1, 1, 1, 0.25f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Ghost_Run_L", Ghost_Run_L, Vector2::Zero, 1, 1, 1, 0.25f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"gDamaged_R", gDamaged_R, Vector2::Zero, 1, 1, 1, 0.15f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"gDamaged_L", gDamaged_L, Vector2::Zero, 1, 1, 1, 0.15f, 255, 0, 255);

		EnemyAnimator->CreateAnimation(L"Ghost_DieR", Ghost_DieR, Vector2::Zero, 4, 1, 4, 0.1f, 255, 0, 255);
		EnemyAnimator->CreateAnimation(L"Ghost_DieL", Ghost_DieL, Vector2::Zero, 4, 1, 4, 0.1f, 255, 0, 255);
		//
		// ----- Candle
		EnemyAnimator->CreateAnimation(L"Candle", candle, Vector2::Zero, 1, 1, 1, 0.1f, 255, 0, 255);
		//
		Enemy_TR = GetComponent<Transform>();
		EnemyCollider = AddComponent<Collider>();
		EnemyCollider->setRGB(0, 255, 0);

		// 타입에 따른 생성 정보
		switch (eType)
		{
		case(eEnemyType::BLACK):
		{
			EnemyAnimator->Play(L"RightWalk", true);
			monster_hp = 90;
			Enemy_vel = vel_type1;
			Enemy_TR->setScale(Vector2(2.4f, 2.4f));
			EnemyCollider->setCenter(Vector2(-5, -11));
			EnemyCollider->setSize(Vector2(48, 28)); // 50,28
		}
			break;
		case(eEnemyType::ZOMBIE):
		{
			EnemyAnimator->Play(L"Zombie_MoveR", true);
			monster_hp = 140;
			Enemy_vel = vel_type2;
			Enemy_TR->setScale(Vector2(2.0f, 2.0f));
			EnemyCollider->setCenter(Vector2(-10, -22));
			EnemyCollider->setSize(Vector2(47,55)); // 50,70
		}
			break;
		case(eEnemyType::SKULL):
		{
			EnemyAnimator->Play(L"Skull_MoveR", true);
			monster_hp = 200;
			Enemy_vel = vel_type3;
			Enemy_TR->setScale(Vector2(2.7f, 2.7f));
			EnemyCollider->setCenter(Vector2(-7, -27));
			EnemyCollider->setSize(Vector2(60, 67)); // 50,70
		}
		break;
		case(eEnemyType::GHOST):
		{
			EnemyAnimator->Play(L"Ghost_Run_R", true);
			monster_hp = 300;
			Enemy_vel = vel_type4;
			Enemy_TR->setScale(Vector2(2.2f, 2.2f));
			EnemyCollider->setCenter(Vector2(0, -30));
			EnemyCollider->setSize(Vector2(64, 78));
		}
		break;
		case(eEnemyType::DRAGON):
		{
			EnemyAnimator->Play(L"Dragon_AttackR", true);
			monster_hp = 9999;
			Enemy_vel = 0;
			Enemy_TR->setScale(Vector2(2.2f, 2.2f));
			EnemyCollider->setCenter(Vector2(-10, -27));
			EnemyCollider->setSize(Vector2(46, 71));
		}
		break;
		case(eEnemyType::CANDLE):
		{
			EnemyAnimator->Play(L"Candle", true);
			monster_hp = 30;
			Enemy_vel = 0;
			Enemy_TR->setScale(Vector2(1.8f, 1.8f));
			EnemyCollider->setCenter(Vector2(-9, -28));
			EnemyCollider->setSize(Vector2(36, 53));
		}
		break;
		}
		//
		eState = eEnemyState::Move;

		damaged_Sound 
			= ResourceManager::Load<Sound>(L"Damaged_Sound", L"..\\Resources\\Sound\\sfx_enemyHit.wav");

		GameObject::Initialize();
	}
	void Enemy::Update()
	{
		Enemy_TR = GetComponent<Transform>();
		Ppos = Krochi::getPlayerPos(); 
		EnemyCollider->setRGB(0, 255, 0);
		prevPos = Enemy_TR->getPos();
		movePos = prevPos;

		switch (eState)
		{
		case (eEnemyState::Move):
			move();
			break;
		case (eEnemyState::Back_Move):
			back_move();
			break;
		case (eEnemyState::Slow):
			slow();
			break;
		case (eEnemyState::Death):
			death();
			break;
		case(eEnemyState::None):
			none();
			break;
		}
		Enemy_TR->setPos(movePos);

		Distance =
			std::abs(Ppos.x - movePos.x) + std::abs(Ppos.y - movePos.y);

		if (Distance > 1600) // 플레이어와의 거리가 멀어진다면, 위치를 가까이 옮겨줌
			Enemy_TR->setPos(Krochi::getPlayerPos() + Init_Pos);

		if (PlaySceneManager::Play_Time > EnemyManager::boss_Time - 5.6f)
		{
			Enemy_vel = 0.0f;
		}
		if (PlaySceneManager::Play_Time > EnemyManager::boss_Time - 1.5f)
		{
			eState = eEnemyState::Death;
		}
		if (PlaySceneManager::Play_Time > 165.0f)
		{
			if (eType == eEnemyType::DRAGON)
				object::Destory(this);
		}
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

	void Enemy::move()
	{
		if (Enemy::Finded)
		{
			movePos += (Ppos - Enemy_TR->getPos()).Normalize() * Enemy_vel * Time::getDeltaTime();

			if (Ppos.x - 5 > movePos.x)
			{
				switch (eType)
				{
				case eEnemyType::BLACK:
					EnemyAnimator->Play_NO_RE(L"RightWalk", true);
					break;
				case eEnemyType::ZOMBIE:
					EnemyAnimator->Play_NO_RE(L"Zombie_MoveR", true);
					break;
				case eEnemyType::SKULL:
					EnemyAnimator->Play_NO_RE(L"Skull_MoveR", true);
					break;
				case eEnemyType::DRAGON:
					EnemyAnimator->Play_NO_RE(L"Dragon_AttackR", true);
					break;
				case eEnemyType::GHOST:
					EnemyAnimator->Play_NO_RE(L"Ghost_Run_R", true);
					break;
				}
			}

			if (Ppos.x + 5 < movePos.x)
			{
				switch (eType)
				{
					case eEnemyType::BLACK:
						EnemyAnimator->Play_NO_RE(L"LeftWalk", true);
						break;
					case eEnemyType::ZOMBIE:
						EnemyAnimator->Play_NO_RE(L"Zombie_MoveL", true);
						break;
					case eEnemyType::SKULL:
						EnemyAnimator->Play_NO_RE(L"Skull_MoveL", true);
						break;
					case  eEnemyType::DRAGON:
						EnemyAnimator->Play_NO_RE(L"Dragon_AttackL", true);
						break;
					case eEnemyType::GHOST:
						EnemyAnimator->Play_NO_RE(L"Ghost_Run_L", true);
						break;
				}
			}
		}
	}

	void Enemy::slow()
	{
		delay += Time::getDeltaTime();

		/*if(eType != eEnemyType::GHOST)
			movePos = prevPos;*/

		if (delay >= 0.2f)
		{
			if (monster_hp <= 0)
				eState = eEnemyState::Death;
			else
				eState = eEnemyState::Move;

			delay = 0.0f;
		}
	}

	void Enemy::back_move()
	{
		delay += Time::getDeltaTime();

		if (eType == eEnemyType::CANDLE)
		{
			Chicken* chicken = object::Instantiate<Chicken>
				(Enemy_TR->getPos(), eLayerType::ITEMS);

			object::Destory(this);
		}


		float vel = -270.0f;

		if (eType == eEnemyType::DRAGON || eType == eEnemyType::GHOST)
			vel = 0.0f;	

		movePos += (Ppos - Enemy_TR->getPos()).Normalize() * vel * Time::getDeltaTime();

		if (Ppos.x - 5 > movePos.x)
		{
			if (eType == eEnemyType::BLACK)
				EnemyAnimator->Play_NO_RE(L"Damaged_R", true);
			if(eType == eEnemyType::ZOMBIE)
				EnemyAnimator->Play_NO_RE(L"zDamaged_R", true);
			if (eType == eEnemyType::SKULL)
				EnemyAnimator->Play_NO_RE(L"sDamaged_R", true);
			if (eType == eEnemyType::DRAGON)
				EnemyAnimator->Play_NO_RE(L"dDamaged_R", true);
			if (eType == eEnemyType::GHOST)
				EnemyAnimator->Play_NO_RE(L"gDamaged_R", true);
		}
		if (Ppos.x + 5 < movePos.x)
		{
			if (eType == eEnemyType::BLACK)
				EnemyAnimator->Play_NO_RE(L"Damaged_L", true);
			if (eType == eEnemyType::ZOMBIE)
				EnemyAnimator->Play_NO_RE(L"zDamaged_L", true);
			if (eType == eEnemyType::SKULL)
				EnemyAnimator->Play_NO_RE(L"sDamaged_L", true);
			if (eType == eEnemyType::DRAGON)
				EnemyAnimator->Play_NO_RE(L"dDamaged_L", true);
			if (eType == eEnemyType::GHOST)
				EnemyAnimator->Play_NO_RE(L"gDamaged_L", true);
		}

		if (delay >= 0.12f)
		{
			delay = 0.0f;

			if (monster_hp <= 0)
				eState = eEnemyState::Death;
			else
				eState = eEnemyState::Move;
		}
	}
	void Enemy::death()
	{
		if (Ppos.x > movePos.x)
		{
		if (eType == eEnemyType::BLACK)
			EnemyAnimator->Play_NO_RE(L"fly_Die_R", false);
		if (eType == eEnemyType::ZOMBIE)
			EnemyAnimator->Play_NO_RE(L"Zombie_DieR", false);
		if (eType == eEnemyType::SKULL)
			EnemyAnimator->Play_NO_RE(L"Skull_DieR", false);
		if (eType == eEnemyType::GHOST)
			EnemyAnimator->Play_NO_RE(L"Ghost_DieR", false);
		}
		if (Ppos.x < movePos.x)
		{
		if (eType == eEnemyType::BLACK)
			EnemyAnimator->Play_NO_RE(L"fly_Die_L", false);
		if (eType == eEnemyType::ZOMBIE)
			EnemyAnimator->Play_NO_RE(L"Zombie_DieL", false);
		if (eType == eEnemyType::SKULL)
			EnemyAnimator->Play_NO_RE(L"Skull_DieL", false);
		if (eType == eEnemyType::GHOST)
			EnemyAnimator->Play_NO_RE(L"Ghost_DieL", false);
		}
	
		if (EnemyAnimator->IsComplete())
		{
			lv_Item = object::Instantiate<Level_Item>
				(Enemy_TR->getPos(), eLayerType::ITEMS);

			object::Destory(this);

			++Krochi::Death_count;
		}
	}
	void Enemy::dskill_CompleteEvent()
	{
		object::Instantiate<DragonBullet>
			(Enemy_TR->getPos(), eLayerType::SKILL);
	}

	void Enemy::onCollisionEnter(Collider* other)
	{
		if (other->getOwner()->getName() == L"Enemy")
		{
			EnemyCollider->setRGB(255, 0, 0);
			otherEnemy = dynamic_cast<Enemy*>(other->getOwner());

			eState = eEnemyState::Slow;
		}
		if (other->getOwner()->getName() == L"Book")
		{
			damaged_Sound->Play(false);
			EnemyCollider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(Enemy_TR->getPos() + Vector2(3.0f, 0.0f), eLayerType::EFFECT);

			monster_hp -= Krochi::getPlayerPower(L"Book");
			this->eState = eEnemyState::Back_Move;
		}
		if (other->getOwner()->getName() == L"Cross")
		{
			damaged_Sound->Play(false);
			EnemyCollider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(Enemy_TR->getPos() + Vector2(3.0f, 0.0f), eLayerType::EFFECT);
			monster_hp -= Krochi::getPlayerPower(L"Cross");
			this->eState = eEnemyState::Back_Move;
		}
		if (other->getOwner()->getName() == L"Ax1")
		{
			damaged_Sound->Play(false);
			EnemyCollider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(Enemy_TR->getPos() + Vector2(3.0f, 0.0f), eLayerType::EFFECT);
			monster_hp -= Krochi::getPlayerPower(L"Ax1");
			this->eState = eEnemyState::Back_Move;
		}
		if (other->getOwner()->getName() == L"Lightning")
		{
			damaged_Sound->Play(false);
			EnemyCollider->setRGB(255, 0, 0);

			mEffect = object::Instantiate<Effect>
				(Enemy_TR->getPos() + Vector2(3.0f, 0.0f), eLayerType::EFFECT);
			monster_hp -= Krochi::getPlayerPower(L"Lightning");
			this->eState = eEnemyState::Back_Move;

		}
	}

	void Enemy::onCollisionStay(Collider* other)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			Enemy_vel = 0.0f;
		}
		if (other->getOwner()->getName() == L"Radar")
		{
			Enemy::Finded = true;
		}
	}

	void Enemy::onCollisionExit(Collider* other)
	{
		if (other->getOwner()->getName() == L"Radar")
		{
			Enemy::Finded = false;
		}

		if (other->getOwner()->getName() == L"Player")
		{
			if (eType == eEnemyType::BLACK)
				Enemy_vel = vel_type1;
			if (eType == eEnemyType::ZOMBIE)
				Enemy_vel = vel_type2;
			if (eType == eEnemyType::SKULL)
				Enemy_vel = vel_type3;
			if (eType == eEnemyType::GHOST)
				Enemy_vel = vel_type4;
		}
	}
}