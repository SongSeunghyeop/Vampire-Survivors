#pragma once
#include "myGameObject.h"
#include "myResourceManager.h"
#include "myTransform.h"
#include "myInput.h"
#include "myImage.h"
#include "myCollider.h"
#include "myAnimator.h"
#include "Sound.h"
#include "Time.h"
#include "myObject.h"
#include "Krochi.h"
#include "EnemyManager.h"
#include "Radar.h"

namespace my
{
	class Lightning;
	class Book;
	class Ax1;
	class Ax2;
	class Cross;

	enum class eSkillname {
		LIGHT,
		CROSS,
		AX1,
		AX2,
		BOOK,

	};
	class SkillManager : public GameObject
	{
	public:
		void setSkillScale(float f) { skill_scale = f; }
		void setSustain_time(float t) { sustain_time = t; }
		void setR(int r) { R = r; }
		virtual void setVel(float v) { Skill_Vel = v; }
		void setDistance(float d) { distance = d; }

		void skill_Instantiate(eSkillname skillname, int num);
	
		virtual void Update() override;

	protected:
		Animator* Skill_Animator;
		Transform* Skil_Tr;
		Collider* Skill_Collider;
		Image* Skill_Image;
		Image* Skill_Image2;

		Vector2 dir;
		Vector2 rotation;

		Vector2 Skill_Pos;
		Vector2 EnemyPos;

		float mTime;
		float Skill_Vel;
		int R;
		float skill_scale;
		float sustain_time;
		float distance;
		float active_time;
		Sound* skill_sound;

		Lightning* light;
		Book* book;
		Ax1* ax1;
		std::vector<Ax2*> axes;
		Cross* cross;
		float axTime = 0.0f;
		int randNum = 0;

		bool ax2_Init = false;
	};
}

