#include "Texture.h"

namespace engine
{

	Texture::Texture()
	{
	}


	Texture::~Texture()
	{
	}

	void Texture::TextureInit(std::string textureName)
	{
		///Diffuse map
		SDL_Surface* surface = IMG_Load(textureName.c_str());
		if (surface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", textureName.c_str(), IMG_GetError());
		}
		else
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				surface->w,
				surface->h,
				0, GL_RGB, GL_UNSIGNED_BYTE,
				surface->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
}