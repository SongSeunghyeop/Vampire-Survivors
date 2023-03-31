#pragma once
#include "myResource.h"

namespace my
{
	class ResourceManager
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& key)
		{
			//���ҽ� �ʿ��� ������ Ž��, �����Ͱ� �ִٸ� �ش� ������ ��ȯ
			// ���ٸ� end ��ȯ
			std::map<std::wstring, Resource*> ::iterator it = mResources.find(key);

			if (it != mResources.end()) // it���� �迭�� �������� �ʴٸ� end��ȯ
				return dynamic_cast<T*>(it->second); // ���ҽ� ��ȯ

			return NULL; // it���� �迭�� ���� ���ٸ� �ΰ� ��ȯ
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path) // Image �Ǵ� Sound
		{
			T* resource = ResourceManager::Find<T>(key);

			if (resource != NULL) // ���ҽ��� �迭�� �̹� �־��ٸ�
				return resource;

			resource = new T();

			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return NULL;
			}

			resource->setKey(key);
			resource->setPath(path);

			mResources.insert(make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}
		template <typename T>
		static void Insert(const std::wstring& key, T* resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}

		static void Release()
		{
			for (auto pair : mResources)
			{
				delete pair.second;
				pair.second = NULL;
			}
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}

