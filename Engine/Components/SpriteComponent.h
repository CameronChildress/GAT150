#pragma once

#include "RenderComponent.h"
#include "Graphics/Texture.h"

namespace nc
{
	class SpriteComponent : public RenderComponent
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual Object* Clone() override { return new SpriteComponent{ *this }; }

		void Read(const rapidjson::Value& value);

		virtual void Update() override;
		virtual void Draw() override;

	protected:
		std::string m_textureName;
		Vector2 m_origin;
		SDL_Rect m_rect{ 0, 0, 0, 0 };
	};
}