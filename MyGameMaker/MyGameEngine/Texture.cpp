#include "Texture.h"

#include <SDL2/SDL_image.h>

#include "Renderer.h"

Texture::Texture(const string& path, unsigned int* valor) : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
m_Width(0), m_Height(0), m_BPP(0)
{
	// Carga la imagen usando SDL_image
	SDL_Surface* imageSurface = IMG_Load(path.c_str());
	if (!imageSurface) {
		printf("Error al cargar imagen: %s\n", IMG_GetError());
		return;
	}

	// Determina el formato de la imagen para OpenGL
	GLenum format;
	if (imageSurface->format->BytesPerPixel == 4) { // RGBA
		format = (imageSurface->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
	}
	else if (imageSurface->format->BytesPerPixel == 3) { // RGB
		format = (imageSurface->format->Rmask == 0x000000ff) ? GL_RGB : GL_BGR;
	}
	else {
		printf("Formato de imagen no compatible\n");
		SDL_FreeSurface(imageSurface);
		return;
	}

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	// Generar Mipmap y configurar parámetros de textura
	glGenerateMipmap(GL_TEXTURE_2D);
	//GL_TEXTURE_MIN_FILTER per si la imatge es mes gran que el pla on es pinta i GL_TEXTURE_MAG_FILTER pel contrari
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//S = X, T = Y (entiendo que es para que cuadre el x = 0 i y = 0 en las mismas del plano
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	glTexImage2D(GL_TEXTURE_2D, 0, format, imageSurface->w, imageSurface->h, 0, format, GL_UNSIGNED_BYTE, imageSurface->pixels);
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	// Liberar la superficie de SDL
	SDL_FreeSurface(imageSurface);

	if (valor != nullptr)
	{
		*valor = m_RendererID;
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
