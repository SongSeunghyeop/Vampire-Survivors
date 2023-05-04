#include "SkillManager.h"
#include "Book.h"
#include "Ax1.h"
#include "Ax2.h"
#include "Cross.h"
#include "Lightning.h"

namespace my
{
	void SkillManager::Update()
	{
		if (ax2_Init && axes.back()->getState() != GameObject::eState::Active)
		{
			axTime += Time::getDeltaTime();

			for (int i = 0; i < axes.size(); i++)
			{
				if (axTime >= (i + 1) * 0.03f && axes.at(i)->getState() != GameObject::eState::Active)
					axes.at(i)->setState(GameObject::eState::Active);
			}

			if (axes.back()->getState() == GameObject::eState::Active)
			{
				axTime = 0.0f;
				ax2_Init = false;
				axes.clear();
			}
		}
	}
	void SkillManager::skill_Instantiate(eSkillname skillname, int num)
	{
		switch (skillname)
		{
			case eSkillname::LIGHT:
			{
				if (Radar::getEnemyNum() < num)
					num = Radar::getEnemyNum();

				for (int i = 0; i < num; i++)
				{
					randNum = rand() % 1000;

					Lightning* light
						= object::Instantiate<Lightning>
						(Radar::getRandomEnemyPos(randNum) + Vector2(12.0f, -174.0f), eLayerType::SKILL);
				}
			}
			break;
			case eSkillname::AX1:
			{
				for (int i = 0; i < num; i++)
				{
					int r = rand() % 70 + 190; // 190 ~ 260
					int v = rand() % 400 + 500; // 400 ~ 900

					ax1 = object::Instantiate<Ax1>(Krochi::getPlayerPos(), eLayerType::SKILL);
					ax1->setVel(v);
					ax1->setR(r);
				}
			}
			break;
			case eSkillname::AX2:
			{
				for (int i = 0; i < 18; i++)
				{
					Ax2* ax2;
					ax2 = object::Instantiate<Ax2>(Krochi::getPlayerPos(), eLayerType::SKILL);
					ax2->setR(i * 20);
					ax2->setState(GameObject::eState::None);
					axes.push_back(ax2);
				}
				ax2_Init = true;
			}
			break;
			case eSkillname::CROSS:
			{
				for (int i = 0; i < num; i++)
				{
					int r = rand() % 360 + 1;

					cross = new Cross();
					Scene* scene = SceneManager::getActiveScene();
					scene->AddGameObj(cross, eLayerType::SKILL);
					cross->GameObject::GetComponent<Transform>()->setPos(Krochi::getPlayerPos());
					cross->setSkillScale(2.2f + num * 0.1);
					cross->setR(r);
					cross->Initialize();
				}
			}
			break;
			case eSkillname::BOOK:
			{
				for (int i = 0; i < num; i++)
				{
					book = object::Instantiate<Book>(Krochi::getPlayerPos(), eLayerType::SKILL);
					book->setR(360 / num * (i));
					book->setDistance(50 + (num * 20));
					book->setVel(145 + (num * 10));
					book->setSustain_time(3.5f + (num * 0.2f));
				}
			}
			break;
		}
	}
}