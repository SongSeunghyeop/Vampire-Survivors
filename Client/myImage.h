#pragma once
#include "myResource.h"

namespace my
{
	class Image : public Resource // �̹������ҽ�
	{
	public:
		static Image* Create(const std::wstring& name, UINT widht, UINT height);
		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override; // ���ҽ� Load �Լ� ���

		HDC GetHdc() { return mHdc; }
		HBITMAP GetBitmap() { return mBitmap; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}