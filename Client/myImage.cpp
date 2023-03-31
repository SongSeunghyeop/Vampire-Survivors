#include "myImage.h"
#include "myApplication.h"
#include "myResourceManager.h"

extern my::Application myapplication;

namespace my
{
	Image* Image::Create(const std::wstring& name, UINT widht, UINT height)
	{
		if (widht == 0 || height == 0)
			return nullptr;

		Image* image = ResourceManager::Find<Image>(name);
		if (image != nullptr)
			return image;

		image = new Image();
		HDC mainHdc = myapplication.GetHdc();

		image->mBitmap = CreateCompatibleBitmap(mainHdc, widht, height);
		image->mHdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		image->mWidth = widht;
		image->mHeight = height;

		image->setKey(name);
		ResourceManager::Insert<Image>(name, image);

		return image;
	}

	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{

	}
	Image::~Image()
	{

	}
	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr  // 받은 이미지 비트맵에 저장
			, path.c_str(), IMAGE_BITMAP
			, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr) // 비트맵에 받은 이지지가 없으면 
			return E_FAIL; // false 리턴 

		BITMAP bitInfo = {}; // 비트맵의 폭, 높이, 색상 등의 정보
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth; // 받은 리소스를 저장한 비트맵의 가로
		mHeight = bitInfo.bmHeight; // 받은 리소스를 저장한 비트맵의 세로

		HDC mainDC = myapplication.GetHdc();
		mHdc = CreateCompatibleDC(mainDC); // 원본의 DC와 호환가능한 값으로 초기화

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap); // 방금 만든 캐릭터의 dc와 bmp를 받고 기존 bmp 
		DeleteObject(oldBitmap); // 삭제

		return S_OK;
	}
}
