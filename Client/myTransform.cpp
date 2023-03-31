#include "myTransform.h"

namespace my
{
	Transform::Transform()
		:Component(eComponentType::TRANSFORM)
		, mPos(Vector2::Zero)
		, mScale(Vector2(1.0f,1.0f))
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::Render(HDC hdc)
	{
	}
	void Transform::Release()	
	{

	}
	void Transform::setPos(Vector2 pos)
	{
		mPos = pos;
	}
	void Transform::setPos(int a, int b)
	{
		mPos.x = a;
		mPos.y = b;
	}
	void Transform::setScale(Vector2 scale)
	{
		this->mScale.x = scale.x;
		this->mScale.y = scale.y;
	}
	void Transform::setScale(float a,float b)
	{
		this->mScale.x = a;
		this->mScale.y = b;
	}
	Vector2 Transform::getPos()
	{
 		return mPos;
	}
	Vector2 Transform::getScale()
	{
		return mScale;
	}
}