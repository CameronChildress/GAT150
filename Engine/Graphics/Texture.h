#pragma once

#include <SDL.h>
#include <string>

#include "Math/Vector2.h"
#include "Resources/Resource.h"

namespace nc
{
	class Texture : public Resource
	{
	public:
		bool Create(const std::string& name, void* renderer) override;
		void Destroy() override;

		void Draw(const Vector2& position, float angle = 0, const Vector2& scale = { 1, 1 }, const Vector2& origin = { 0, 0 });
		void Draw(const SDL_Rect& source, const Vector2& position, float angle = 0, const Vector2& scale = { 1, 1 }, const Vector2& origin = { 0, 0 });
		Vector2 GetSize();

	protected:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}