#pragma once
#include "myEntity.h"

namespace my
{
	class Resource // 추상클래스 
	// 리소스에관한 파일 키, 파일 경로와 Load 함수 담당
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0; // 순수가상함수// HRESULT는함수의 상태 정보를 반환 , bool과 유사, 리턴값은 SUCCESSED,FAILED
		
		const std::wstring& GetKey() { return fileKey; } //키 반환
		const std::wstring& GetPath() { return filePath; } // 경로 반환

		void setKey(const std::wstring& key) { fileKey = key; }
		void setPath(const std::wstring& path) { filePath = path; }

	private:
		//map에서의 리소스 키, 경로
		std::wstring fileKey;
		std::wstring filePath;
	};
}