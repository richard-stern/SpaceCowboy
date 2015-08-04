#pragma once

#include <map>
#include <string>

class Texture;

class TextureManager
{
public:
	static TextureManager *GetSingleton()	{ return m_pSingleton; }
	static void CreateSingleton()			{ m_pSingleton = new TextureManager(); }
	static void DestroySingleton()			{ delete m_pSingleton; }

	Texture* LoadTexture(char* szFileName);

private:
	TextureManager();
	~TextureManager();
	static TextureManager * m_pSingleton;

	std::map<std::string, Texture*>* m_pTextureList;
};

