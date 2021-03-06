#pragma once
#include "../Core/Core.h"
#include "../ECS/Component.h"
#include "../Render/TextureAtlas.h"
#include "../Enums/ColorsRGBA.h"

namespace Doom {

	enum DOOM_API RenderType {
		TYPE_2D,
		TYPE_3D,
	};

	class DOOM_API Irenderer : public Component{
	public:

		glm::vec4 m_Color = COLORS::White;
		Shader* m_Shader = nullptr;
		RenderType m_RenderType = RenderType::TYPE_2D;

		Irenderer() {}
		virtual ~Irenderer() {}

		virtual void Render() {}
	};

}