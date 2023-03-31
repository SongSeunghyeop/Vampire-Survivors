#pragma once
#include "VampireEngine.h"

namespace my 
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void setName(const std::wstring& name) { mName = name; }
		std::wstring& getName() { return mName; }
		void SetID(UINT64 id) { mID = id; }
		UINT64 GetID() { return mID; }

	private:
		std::wstring mName;
		UINT64 mID;
	};
}
