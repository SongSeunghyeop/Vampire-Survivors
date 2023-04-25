#include "Cutton.h"
#include "Time.h"
#include "myResourceManager.h"

namespace my
{
	Cutton::Cutton()
	{
		Cutton_on = false;
	}
	Cutton::~Cutton()
	{

	}
	void Cutton::Initialize()
	{
		Black = ResourceManager::Load<Image>(L"Black", L"..\\Resources\\Black.bmp");
		GameObject::Initialize();
	}
	void Cutton::Update()
	{
		GameObject::Update();
	}
	void Cutton::Render(HDC hdc)
	{
		if (Cutton_on == false)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 100;//

			AlphaBlend(hdc, -1, -1
				, 1301, 801
				, Black->GetHdc()
				, 0, 0
				, Black->GetWidth(), Black->GetHeight()
				, func);

			Cutton_on = true;
		}

		GameObject::Render(hdc);
	}
	void Cutton::Release()
	{
		GameObject::Release();
	}
}