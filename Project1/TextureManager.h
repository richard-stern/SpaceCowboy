#pragma once
#include <map>
class Texture;

class TextureManager
{
public:
	static TextureManager *GetSingleton()	{ return m_pSingleton; }
	static void CreateSingleton()			{ m_pSingleton = new TextureManager(); }
	static void DestroySingleton()			{ delete m_pSingleton; }

	//Used to load textures more efficiently.
	//If a texture is asked for that has already been loaded, returns the existing loaded texture instead of loading it again.
	Texture* LoadTexture(char* szFileName);

private:
	TextureManager();
	~TextureManager();
	static TextureManager * m_pSingleton;

	std::map<char*, Texture*> m_textureList;
};

