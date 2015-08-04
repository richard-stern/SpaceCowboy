/* -----------------------------------------------------------------------------
Author:			Aaron Cox

Description:		
This Font class will load *.fnt files exported from by AngelCode's Bitmap Font Generator
The Bitmap Font Generator can be downloaded from: http://www.angelcode.com/products/bmfont/
This class will provide the nescessary code for loading a font,
however will not supply rendering information.

Font file used for loading only.
The SpriteBatch can render it...

Usage:

// load font
Font *font = new Font("./Fonts/someFont.fnt");

// later in code
spritebatch->DrawString( font, "hello world", xPos, yPos );


// cleanup
delete font;
-----------------------------------------------------------------------------*/

#ifndef FONT_H
#define FONT_H

#include <map>
#include <vector>

class Texture;

class Font
{
public:

	struct CharInfo
	{
		short			x, y;				// represents the position top left pixel of the character within the texture
		char			xOffset, yOffset;	// represents the ???
		unsigned char	width, height;		// the width in pixels of the character
		char			xAdvance;			// the amount of space to move along the xAxis for the next character

		CharInfo() : x(0), y(0), xOffset(0), yOffset(0), width(0), height(0), xAdvance(0) {}
	};

	struct Rect
	{
		float x, y, w, h;
	};

	Font(const char *filename);
	~Font();

	Texture *GetFontBitmap();

	float GetLineHeight();

	char GetKerning(unsigned char first, unsigned char second);

	const CharInfo *GetCharInfo( unsigned char character);

	Rect GetCharacterTexCoord(const CharInfo *info);

private:

	bool LoadFont(const char *filename);

	unsigned char m_lineHeight;

	unsigned char m_base;
	short m_width;
	short m_height;
	
	unsigned short m_kernCount;
	bool m_useKerning;

	std::vector<CharInfo> m_characters;

	// map of map
	// contains kerning information m_kerning[firstCharacter][secondCharacter] = kerningAmount
	std::map< unsigned char, std::map< unsigned char, char > > m_kerning;

	Texture *m_texture;
};

#endif