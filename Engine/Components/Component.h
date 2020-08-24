#pragma once

#include "Objects/GameObject.h"

namespace nc
{
	class GameObject;

	class Component : public Object
	{
		virtual void Update() = 0;

		friend class GameObject;

	protected:
		GameObject* m_owner{ nullptr };
	};
}