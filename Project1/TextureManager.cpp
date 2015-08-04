#include "TextureManager.h"
#include "Texture.h"
#include <string>

TextureManager* TextureManager::m_pSingleton = nullptr;

TextureManager::TextureManager()
{
	m_pTextureList = new std::map<std::string, Texture*>();
}

TextureManager::~TextureManager()
{
	auto it = m_pTextureList->begin();
 
	while(it != m_pTextureList->end())
	{
	  delete it->second;
	  it++;
	}
 
	m_pTextureList->clear();
	delete m_pTextureList;
}

Texture* TextureManager::LoadTexture(char* szFileName)
{
	std::string filename = "./Images/";
	filename += szFileName;

	//strcat_s(filename, 100, "./Images/");
	//strcat_s(filename, 100, szFileName);

	auto it = m_pTextureList->find(filename);

	if(it == m_pTextureList->end())
	{
		Texture* pNewTexture = new Texture(filename.c_str());
		m_pTextureList->insert( std::pair<std::string, Texture*>(filename, pNewTexture) );
		return pNewTexture;
	}
	else
	{
	   return it->second;
	}
}