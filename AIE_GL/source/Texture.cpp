#include "Texture.h"

#include "glfw3.h"
#include "lodepng.h"
#include <vector>

#include <assert.h>

Texture::Texture(const char *filename)
{
	m_glTextureHandle = LoadTexture(filename, &m_width, &m_height);
}

Texture::Texture(unsigned int width, unsigned int height, unsigned int *pixels)
{
	m_width = width;
	m_height = height;

	glGenTextures(1, &m_glTextureHandle);
	glBindTexture(GL_TEXTURE_2D, m_glTextureHandle);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);


	glBindTexture( GL_TEXTURE_2D, 0 );
}

Texture::~Texture()
{
	DeleteTexture( m_glTextureHandle );
}

unsigned int Texture::GetWidth()			const	{	return m_width;				}
unsigned int Texture::GetHeight()			const	{	return m_height;			}
unsigned int Texture::GetTextureHandle()	const	{	return m_glTextureHandle;	}

// Load PNG images only
// Returns an OpenGL texture ID
// out_width and out_height are pointers, the function will return the textures width and height
// through these paramaters if not NULL
unsigned int Texture::LoadTexture(const char *filename, unsigned int *out_width, unsigned int *out_height)
{
	unsigned int width	= 0;
	unsigned int height = 0;
	std::vector< unsigned char > pixels;
	std::vector< unsigned char > flipped;

	// populates "pixels" vector with pixel data formated as RGBA
	// width and height are passed in as reference. If the function succeeds, 
	// with and height should be populated with the loaded textures widht and height in pixels
	lodepng::decode( pixels, width, height, filename );

	if( out_width	!= NULL )	*out_width	= width;
	if( out_height	!= NULL )	*out_height = height;

	// pixels are upside down in lodepng...
	// this will invert the raw pixel data again
	unsigned int row_bytes = width * 4;
	for (unsigned int i = 0; i < height; i++)
	{
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        //memcpy(*(&pixels[0])+(row_bytes * (height-1-i)), row_pointers[i], row_bytes);
		for(unsigned int j = 0; j < row_bytes; j++)
		{
			flipped.push_back( pixels[((height - i - 1) * row_bytes) + j] );
		}
    }

	// TODO:
	//-------------------------------------------------------------------------
	// Procedrally genorate an "ERROR" texture
	// and load it into memory for any textures that could not be found
	//-------------------------------------------------------------------------

	// create an openGL texture
	//-------------------------------------------------------------------------

		unsigned int textureID = 0;
		glGenTextures(1, &textureID); // genorate the texture and store the unique id in textureID

		glBindTexture(GL_TEXTURE_2D, textureID); // make the genorated texture the current texture

		// send the pixel data to the current texture
		// NOTE: we need to tell openGL what the current format of the pixels is in RAM,
		//       we then need to tell it what format we want the pixels to be formatted in within video memory (openGL will do the conversion)
		//		 we also need to tell it the size of each color channel, which is GL_UNSIGNED_BYTE (one byte each for Red, Green, Blue and Alpha)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &flipped[0]);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, 0);

	//-------------------------------------------------------------------------

	// return the genorated texture ID
	return textureID;
}

// unloads the texture from graphics memory
// expects a valid openGL texture ID, as returned from the LoadTexture function
void Texture::DeleteTexture(unsigned int textureID)
{
	// yep, this is a lit easier than the Load texture function
	glDeleteTextures( 1, &textureID );
}