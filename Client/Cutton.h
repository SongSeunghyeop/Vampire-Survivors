#pragma once
#include "MyGameObject.h"
#include "myImage.h"
namespace my
{
	class Cutton : public GameObject
	{
	public:
		Cutton();
		~Cutton();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		void setCutton(bool b) { Cutton_on = b; };
	private:
		//double mSecond;
		Image* Black;
		bool Cutton_on;
	};
}

