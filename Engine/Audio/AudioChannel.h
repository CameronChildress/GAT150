#pragma once
#include <fmod.hpp>

namespace nc
{
	class AudioChannel
	{
	public:
		AudioChannel() = default;
		AudioChannel(FMOD::Channel* channel) : m_channel{ channel } {}

		bool IsPlaying();
		void Stop();

	protected:
		FMOD::Channel* m_channel{ nullptr };
	};
}