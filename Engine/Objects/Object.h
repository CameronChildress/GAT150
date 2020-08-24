#pragma once

#include "Core/Json.h"

namespace nc
{
	class Object
	{
	public:
		virtual bool Create(void* data = nullptr) = 0;
		virtual void Destroy() = 0;
		virtual Object* Clone() { return nullptr; }


		virtual void Read(const rapidjson::Value& value) {}

		template<typename T>
		static Object* Instantiate()
		{
			T* instance = new T;
			return instance;
		}
	};
}