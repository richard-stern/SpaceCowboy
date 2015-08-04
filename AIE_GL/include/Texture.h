/*-----------------------------------------------------------------------------
Author: Aaron Cox
Description:	Basic Texture class...
				does nothing special except wrap up basic texture information like width, 
				height and the handle provided by openGL
Usage:
-------------------------------------------------------------------------------

	// creating a texture
	Texture *pTexture = new Texture( "image.png" )

	pTexture->GetWidth();
	pTexture->GetHeight();
	pTexture->GetTextureHandle();

	// rendering can be preformed via the SpriteBatch!

	delete pTexture;

-----------------------------------------------------------------------------*/

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:

	// overloaded constructor
	// loads a texture given the filename...
	// program will crash if texture was unable to be found.
	Texture(const char *filename);

	// overloaded constructor
	// loads a texture given the filename...
	// program will crash if texture was unable to be found.
	Texture(unsigned int width, unsigned int height, unsigned int *pixels = 0);

	// destructor
	// frees the texture from video memory
	virtual ~Texture();

	unsigned int GetWidth()			const;
	unsigned int GetHeight()		const;

	// returns the texture handle genorated by openGL during load
	// glGenTextures...
	unsigned int GetTextureHandle()	const;

protected:

	unsigned int	m_width;
	unsigned int	m_height;
	unsigned int	m_glTextureHandle;

private:

	// Load PNG images only
	// Returns an OpenGL texture ID
	// out_width and out_height are pointers, the function will return the textures width and height
	// through these paramaters if not NULL
	static unsigned int LoadTexture(const char *filename, unsigned int *out_width = nullptr, unsigned int *out_height = nullptr);

	// unloads the texture from graphics memory
	// expects a valid openGL texture ID, as returned from the LoadTexture function
	static void DeleteTexture(unsigned int textureID);

};

#endif