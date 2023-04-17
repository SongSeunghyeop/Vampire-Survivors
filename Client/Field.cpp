#include "myResourceManager.h"
#include "Field.h"
#include "Time.h"
#include "myCamera.h"
#include "Krochi.h"

extern my::Application myapplication;

namespace my
{
	Field::Field()
		:width(0)
		,height(0)
	{

	}
	Field::~Field()
	{

	}
	void Field::Initialize()
	{
		fieldImg = ResourceManager::Load<Image>(L"Field", L"..\\Resources\\Field_All.bmp");

		GameObject::Initialize();
	}
	void Field::Update()
	{
		GameObject::Update();
	}
	void Field::Render(HDC hdc)
	{
		Vector2 pos = Camera::CaluatePos(Vector2::Zero);
		//Å©·©Å° ¹Ú½º

		pos.x -= width;
		pos.y -= height;

		StretchBlt(hdc, (int)pos.x - 3800 , (int)pos.y - 3800
				, fieldImg->GetWidth(), fieldImg->GetHeight(), fieldImg->GetHdc(), 0, 0, 
				fieldImg->GetWidth(), fieldImg->GetHeight(),SRCCOPY);

		if ((int)pos.x - 3800 > -3000)
		{
			width += 3000;
		}
		if ((int)pos.x - 3800 < -6000) // 4500
		{
			width -= 3000;
		}
		if ((int)pos.y - 3800  > -3000 )
		{
			height += 3000;
		}
		if ((int)pos.y - 3800 < -6000) // 5282
		{
			height -= 3000;
		}
 	}
	void Field::Release()
	{
		GameObject::Release();
	}
}
