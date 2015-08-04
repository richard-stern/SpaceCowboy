#include "stdlib.h"
#include "TextureManager.h"
#include "Texture.h"

TextureManager* TextureManager::m_pSingleton = nullptr;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	for (auto iter = m_textureList.begin(); iter != m_textureList.end(); iter++)
	{
		delete iter->second;
	}
}

Texture* TextureManager::LoadTexture(char* szFileName)
{
	if (m_textureList.find(szFileName) != m_textureList.end())
	{
		// texture is loaded, return existing pointer
		return m_textureList[szFileName];
	}
	else
	{
		// texture is not loaded, load the texture

		// construct filename
		char filename[100] = "./Images/";
		strcat_s(filename, szFileName);
		//strcat(filename, ".png");

		// add texture to texture list and return
		m_textureList[szFileName] = new Texture(filename);
		return m_textureList[szFileName];
	}
	return nullptr;
}