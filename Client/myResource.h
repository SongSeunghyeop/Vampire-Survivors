#pragma once
#include "myEntity.h"

namespace my
{
	class Resource // �߻�Ŭ���� 
	// ���ҽ������� ���� Ű, ���� ��ο� Load �Լ� ���
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0; // ���������Լ�// HRESULT���Լ��� ���� ������ ��ȯ , bool�� ����, ���ϰ��� SUCCESSED,FAILED
		
		const std::wstring& GetKey() { return fileKey; } //Ű ��ȯ
		const std::wstring& GetPath() { return filePath; } // ��� ��ȯ

		void setKey(const std::wstring& key) { fileKey = key; }
		void setPath(const std::wstring& path) { filePath = path; }

	private:
		//map������ ���ҽ� Ű, ���
		std::wstring fileKey;
		std::wstring filePath;
	};
}