#pragma once

#include "Resources/Resource.h"
#include "AudioChannel.h"

#include <fmod.hpp>

namespace nc
{
	class Sound : public Resource
	{
	public:
		virtual bool Create(const std::string& name, void* data = nullptr) override;
		virtual void Destroy() override;

		AudioChannel Play(bool loop = false);

	private:
		FMOD::System* m_system{ nullptr };
		FMOD::Sound* m_sound{ nullptr };
	};
}
