#pragma once

#include <string>
#include "GL/glew.h"
#include "SDL.h"
#include <SDL_image.h>

namespace engine
{

	class Texture
	{
	public:
		Texture();
		~Texture();

		void TextureInit(std::string textureName);
		GLuint getTexture() { return texture; }

	private:

		GLuint texture;
	};

}