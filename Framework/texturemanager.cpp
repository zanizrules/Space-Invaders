
// This include:
#include "texturemanager.h"

// Local includes:
#include "texture.h"
#include "logmanager.h"

// Library includes:
#include <SDL.h>
#include <cassert>

TextureManager::TextureManager()
: m_pRenderer(0)
{

}

TextureManager::~TextureManager()
{
	std::map<std::string, Texture*>::iterator iter;
	for (iter = m_pLoadedTextures.begin(); 
		iter != m_pLoadedTextures.end(); iter++)
	{
		delete iter->second;
		iter->second = 0;
	}
}

bool TextureManager::Initialise(SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;

	return true;
}

Texture* TextureManager::GetTexture(const char* pcFilename)
{
	Texture* pTexture = 0;

	if (m_pLoadedTextures.find(pcFilename) == m_pLoadedTextures.end())
	{
		// Not already loaded... so load...
		pTexture = new Texture();
		if (!pTexture->Initialise(pcFilename, m_pRenderer))
		{
			LogManager::GetInstance().Log("Texture failed to initialise!");
		}
		
		m_pLoadedTextures[pcFilename] = pTexture;
	}
	else
	{
		// Is already loaded...
		pTexture = m_pLoadedTextures[pcFilename];
	}

	return (pTexture);
}

