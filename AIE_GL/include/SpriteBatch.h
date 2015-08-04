// Author: Aaron
// Description: Sprite Batch interface class and Factory

// Usage:
/*-----------------------------------------------------------------------------

	// creating a sprite batch instance, this should happen once, not every frame
	SpriteBatch *sb = SpriteBatch::Factory::Create( pGameInstance, SpriteBatch::IMIDIATE );

	Texture *pTexture = new Texture("./Images/myImage.png");

	// rendering code

		sb->Begin(); // begin rendering 

		sb->DrawSprite(pTexture, xPos, yPos);
		sb->DrawSprite(pTexture, xPos, yPos, width, height);

		sb->SetRenderColor(0xFF0000FF);			// render red for future draw calls
		sb->DrawSprite(pTexture, xPos, yPos); 
		sb->DrawSprite(pTexture, xPos, yPos); // these sprite should be drawn with the color set above ( red )


		sb->End();	// end rendering


	// when its time to destroy the object
	SpriteBatch::Factory::Destroy( sb );

-----------------------------------------------------------------------------*/

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

class Application;
class Texture;
class RenderTexture;
class Font;


class SpriteBatch
{
public:

	enum ERenderMode
	{
		GL3,
	};

	class Factory
	{
	public:
		static SpriteBatch * Create(Application *pApp, ERenderMode mode);
		static void Destroy(SpriteBatch *pSpriteBatch);
	};

	// draw calls below can only be processed between the begin() and end() function calls.
	virtual void Begin()								= 0;
	virtual void End()									= 0;

	// draw a texture at the specified position, size, origin
	virtual void DrawSprite( Texture *texture, float xPos, float yPos, float width = 0.0f, float height = 0.0f, float rotation = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f) = 0;

	// draw a texture that is transformed by a matrix (a pointer to the beginning of 9 floats)
	// the width and height are scailed by the matrix.
	virtual void DrawSpriteTransformed3x3(Texture *texture, float *transformMat3x3, float width = 0.0f, float height = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f)=0;
	
	// draw a texture that is transformed by a matrix (a pointer to the beginning of 16 floats)
	// the width and height are scailed by the matrix.
	virtual void DrawSpriteTransformed4x4(Texture *texture, float *transformMat4x4, float width = 0.0f, float height = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f)=0;

	// draw a string of text.
	// new line character '\n' is supported.
	// xOrigin and yOrigin can be used to specify if the font should be left, right or center aligned.
	virtual void DrawString( Font *pFont, const char *string, float xPos, float yPos, float xOrigin = 0, float yOrigin = 0) = 0;

	// draws a white line from x1,y1 to x2,y2 with the specified thickness.
	virtual void DrawLine( float x1, float y1, float x2, float y2, float thickness = 1.0f ) = 0;

	// change the tint color for rendering
	void SetRenderColor(unsigned int col);
	void SetRenderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	// specify the uv coordinate 
	void SetUVRect(float uvX, float uvY, float uvW, float uvH);
	
	// if set to true, the DrawSpriteTransformed3x3 & DrawSpriteTransformed4x4 functions
	// will be treeted as column major, otherwise, its treeted as row major
	void SetColumnMajor(bool columnMajor);

	void SetCameraPos(float x, float y);
	void GetCameraPos(float* outX, float* outY);
	void GetViewRect(float* outMinX, float* outMinY, float* outMaxX, float* outMaxY);

protected:

	// spritebatch protected, so that it can only be constructed through the "Factory" class
	SpriteBatch(Application *pApp);
	virtual ~SpriteBatch();

	// represents red, green, blue, alpha in the range of 0 - 255
	union
	{
		struct{	unsigned char m_r, m_g, m_b, m_a; };
		unsigned int m_color;
	};

	// represents UV rectangle x, y, widht, height in the range of 0.0f to 1.0f
	float m_uvX, m_uvY, m_uvW, m_uvH; 

	// if set to true, the DrawSpriteTransformed3x3 & DrawSpriteTransformed4x4 functions
	// will be treeted as column major, otherwise, its treeted as row major
	bool m_transformColumnMajor;

	// if the texture specified is invalid, this 1px white texture
	// will be used instead
	Texture *m_nullTexture;

	// needed to accuretly setup 2D rendering orthographic
	Application *m_pApplication;

	// orthographic projection matrix.
	float m_projection[16];

	float m_fCameraX;
	float m_fCameraY;
};

#endif