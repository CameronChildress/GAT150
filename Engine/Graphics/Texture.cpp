#include "pch.h"
#include "Texture.h"
#include "Renderer.h"

namespace nc
{
	bool nc::Texture::Create(const std::string& name, void* renderer)
	{
		m_renderer = static_cast<Renderer*>(renderer)->m_renderer;

		SDL_Surface* surface = IMG_Load(name.c_str());
		if (surface == nullptr)
		{
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_FreeSurface(surface);

		if (m_texture == nullptr)
		{
			return false;
		}

		return true;
	}

	void nc::Texture::Destroy()
	{
		SDL_DestroyTexture(m_texture);
	}

	void nc::Texture::Draw(const Vector2& position, float angle, const Vector2& scale, const Vector2& origin)
	{
		Vector2 size = GetSize();
		size = size * scale;

		Vector2 newPosition = position - (size * origin);

		SDL_Rect rect;
		rect.x = static_cast<int>(newPosition.x);
		rect.y = static_cast<int>(newPosition.y);
		rect.w = static_cast<int>(size.x);
		rect.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
	}

	void Texture::Draw(const SDL_Rect& source, const Vector2& position, float angle, const Vector2& scale, const Vector2& origin)
	{
		Vector2 size = { source.w, source.h };
		size = size * scale;

		Vector2 newPosition = position - (size * origin);

		SDL_Rect rect;
		rect.x = static_cast<int>(newPosition.x);
		rect.y = static_cast<int>(newPosition.y);
		rect.w = static_cast<int>(size.x);
		rect.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(m_renderer, m_texture, &source, &rect, angle, nullptr, SDL_FLIP_NONE);
	}

	Vector2 nc::Texture::GetSize()
	{
		int w, h;
		SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);

		return Vector2{ w, h };
	}
}