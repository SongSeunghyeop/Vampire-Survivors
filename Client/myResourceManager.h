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
			//리소스 맵에서 데이터 탐색, 데이터가 있다면 해당 데이터 반환
			// 없다면 end 반환
			std::map<std::wstring, Resource*> ::iterator it = mResources.find(key);

			if (it != mResources.end()) // it값이 배열에 속해있지 않다면 end반환
				return dynamic_cast<T*>(it->second); // 리소스 반환

			return NULL; // it값이 배열에 아직 없다면 널값 반환
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path) // Image 또는 Sound
		{
			T* resource = ResourceManager::Find<T>(key);

			if (resource != NULL) // 리소스가 배열에 이미 있었다면
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

