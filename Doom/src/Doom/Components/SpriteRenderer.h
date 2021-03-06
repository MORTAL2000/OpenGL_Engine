#pragma once
#ifndef  SPRITERENDERER_H
#define SPRITERENDERER_H

#include "IRenderer.h"
#include "Transform.h"
#include "../Core/Core.h"
#include "../OpenGl/Texture.h"
#include "../Render/TextureAtlas.h"
#include "../Enums/ColorsRGBA.h"
#include "../OpenGl/Shader.h"

namespace Doom {

	class DOOM_API SpriteRenderer : public Irenderer {
	private:

		static unsigned int s_Indices2D[6];
		float m_Mesh2D[16] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f
		};

		Transform* m_Tr = nullptr;

		void Copy(const SpriteRenderer& rhs);

		friend class Transform;
		friend class GameObject;
		friend class Batch;
		friend class Renderer;
		friend class SceneSerializer;
		friend class ComponentManager;
	public:

		TextureAtlas* m_TextureAtlas = nullptr;
		Texture* m_Texture = Texture::s_WhiteTexture;

		SpriteRenderer(const SpriteRenderer& rhs);
		SpriteRenderer();
		~SpriteRenderer();

		void operator=(const SpriteRenderer& rhs);

		void GetTransformedVertices(float* buffer); // returns 8 floats

		virtual void Render() override;

		float GetWidth() const;
		float GetHeight() const;
		float* GetUVs() const;
		
		//Only in int size from 0 to 1 !!!
		void ReversedUvs();
		void OriginalUvs();
		void ReverseUVs();
		void SetUVs(float* uvs);
		void Setlayer(int layer);

	};
}
#endif