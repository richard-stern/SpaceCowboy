#include "Font.h"

#include <string>
#include <fstream>
#include <sstream>
#include "Texture.h"

Font::Font(const char *filename)
{
	m_texture = NULL;
	m_characters.resize(256);

	LoadFont(filename);
}

Font::~Font()
{
	if( m_texture != NULL )
		delete m_texture;
}

bool Font::LoadFont(const char *filename)
{
	std::ifstream	file;
	file.open(filename, std::ios_base::in);
	std::string		line;
	std::string		read, key, value;
	std::size_t		i;

	if( file.good() == false )
		return false; // failed to open...

	// good, now lets try to load the textures.
	std::string fname = filename;
	fname = fname.substr(0, fname.length() - 4);
	fname += "_0.png";

	m_texture = new Texture(fname.c_str());

	while( !file.eof() )
	{
		std::stringstream lineStream;
		std::getline( file, line );
		lineStream << line;

		lineStream >> read;
		if( read == "common" )
		{
			while( !lineStream.eof() )
			{
				std::stringstream converter;
				lineStream >> read;

				i			= read.find('=');
				key			= read.substr(0, i);
				value		= read.substr(i+1);
				converter	<< value;

				short val;

						if( key == "lineHeight" )	{ converter >> val; m_lineHeight	= (unsigned char)val;			}
				else	if( key == "base" )			{ converter >> val; m_base			= (unsigned char)val;			}
				else	if( key == "scaleW" )		{ converter >> val; m_width			= val;			}
				else	if( key == "scaleH" )		{ converter >> val; m_height		= val;			}
				else	if( key == "pages" )		{								}

			}
		}
		else if( read == "char" )
		{
			int charID = 0;
			CharInfo c;

			while( !lineStream.eof() )
			{
				std::stringstream converter;
				lineStream >> read;

				i			= read.find('=');
				key			= read.substr(0, i);
				value		= read.substr(i+1);
				converter	<< value;

				short num;

						if( key == "id" )		{ converter >> charID;					}
				else	if( key == "x" )		{ converter >> num; c.x			= num;						}
				else	if( key == "y" )		{ converter >> num; c.y			= num;						}
				else	if( key == "width" )	{ converter >> num; c.width		= (unsigned char)num;		}
				else	if( key == "height" )	{ converter >> num; c.height	= (unsigned char)num;		}
				else	if( key == "xoffset" )	{ converter >> num; c.xOffset	= (char)num;				}
				else	if( key == "yoffset" )	{ converter >> num; c.yOffset	= (char)num;				}
				else	if( key == "xadvance")	{ converter >> num; c.xAdvance	= (char)num;				}
				else	if( key == "page" )		{															}
			}

			if( charID >= 0 && charID < 266 )
				m_characters[charID] = c;
		}
		if( read == "kernings" )
		{
			while( !lineStream.eof() )
			{
				std::stringstream converter;
				lineStream >> read;

				i			= read.find('=');
				key			= read.substr(0, i);
				value		= read.substr(i+1);
				converter	<< value;

				if( key == "count")	{ converter >> m_kernCount;  }
			}
		}
		else if( read == "kerning" )
		{
			unsigned short first;
			unsigned short second;
			short amount;

			while( !lineStream.eof() )
			{
				std::stringstream converter;
				lineStream >> read;

				i			= read.find('=');
				key			= read.substr(0, i);
				value		= read.substr(i+1);
				converter	<< value;

						if( key == "first" )	{converter >> first;		}
				else	if( key == "second" )	{converter >> second;		}
				else	if( key == "amount"  )	{converter >> amount;		}
 			}
			
			m_kerning[(unsigned char)first][(unsigned char)second] = (char)amount;
		}
	}

	return true;
}

float Font::GetLineHeight()
{
	return m_lineHeight;
}

char Font::GetKerning(unsigned char first, unsigned char second)
{
	if( !( m_useKerning && m_kernCount ) )
		return 0;

	auto it1 = m_kerning.find( first );
	
	if( it1 == m_kerning.end() )
		return 0;

	auto it2 = it1->second.find( second );

	if( it2 == it1->second.end() )
		return 0;

	return it2->second;
}

const Font::CharInfo *Font::GetCharInfo( unsigned char character)
{
	return &m_characters[ character ];
}

Texture *Font::GetFontBitmap()
{
	return m_texture;
}

Font::Rect Font::GetCharacterTexCoord(const CharInfo *info)
{
	float xadv = (float) 1.0f/m_width;
	float yadv = (float) 1.0f/m_height;

	Rect rect;
	rect.x = xadv * info->x;
	rect.y = yadv * info->y;
	rect.w = xadv * info->width;
	rect.h = yadv * info->height;

	// OpenGL Texture coordinates are from bottom left
	// our texture rect is based on top left
	// this converts.
	rect.y = (-rect.y) - rect.h;

	return rect;
}