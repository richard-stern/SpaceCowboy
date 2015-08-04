/*-----------------------------------------------------------------------------
Author:			Aaron Cox
Description:	See SpriteBatch.h for usage!
				
-----------------------------------------------------------------------------*/

#ifndef SPRITEBATCH_GL3_H
#define SPRITEBATCH_GL3_H

#include "SpriteBatch.h"

#include <vector>

class Application;
class Texture;
class Font;

class SpriteBatch_GL3 : public SpriteBatch
{
public:

	SpriteBatch_GL3(Application *pApp);
	virtual ~SpriteBatch_GL3();

	virtual void Begin();
	virtual void End();

	virtual void DrawSprite( Texture *texture, float xPos, float yPos, float width = 0.0f, float height = 0.0f, float rotation = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);

	virtual void DrawSpriteTransformed3x3(Texture *texture, float *transformMat3x3, float width = 0.0f, float height = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);
	virtual void DrawSpriteTransformed4x4(Texture *texture, float *transformMat4x4, float width = 0.0f, float height = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);

	virtual void DrawLine(float x1, float y1, float x2, float y2, float thickness = 1.0f);
	virtual void DrawString(Font *pFont, const char *string, float xPos, float yPos, float xOrigin = 0, float yOrigin = 0);

protected:

	// sprite batch vertex structure
	// 4 of these are created for each sprite rendered to the screen
	// they are stored in the m_vertices array below.
	struct SBVertex
    {
		SBVertex()
		{
			pos[0]		= pos[1]		= pos[2]				= 0.0f;
			color[0]	= color[1]		= color[2]	= color[3]	= 1.0f;
			texcoord[0] = texcoord[1]							= 0.0f;
		}

		SBVertex(float x, float y, float z, float r, float g, float b, float a, float u, float v)
		{
			pos[0]		= x;		pos[1]		= y;	pos[2]		= z;
			color[0]	= r;		color[1]	= g;	color[2]	= g;	color[3] = a;
			texcoord[0] = u;		texcoord[1] = v;
		}

        float  pos[3];			// 12 bytes - offset 0
        float  color[4];		// 16 bytes - offset 12
        float texcoord[2];		// 8 bytes - offset 28

        // sizeof SBVertex 36
    };

protected:

	// helper function
	// returns true if the m_vertices buffer is full
	// returns true if rendering more than m_maxTextures for the batch
	bool ShouldFlush();

	// helper function
	// when rendering a sprite, use the texture
	// this will add the texture to m_activeTextures
	// these are mapped to glActiveTexture(...) so that you can render
	// more than one texture per batch
	unsigned int PushTexture(Texture *texture);
	
	// helper function
	// renders m_vertices to the backbuffer with glDrawElements
	// resets m_vertices, m_indices, m_activeTextuers for rendering a new batch
	void FlushBatch();
	bool IsProcessingRender() { return m_processingRender; }

	// index into the m_vertices array - there are 2048 vertices
	// this keeps track of how many have been used.
	// refers to the next available vertex
	int        m_currentVert;

	// index into the m_indices array - there are 3072 indices
	// this keeps track of how many have been used.
	// refers to the next available indicy
    int        m_currentIndex;
    bool       m_processingRender;

    SBVertex m_vertices[2048];			// 4 verts per sprite = 512 sprites
    unsigned short   m_indices[3072];	// 3 per triangle, 6 per quad = 6 * 512 sprites = 3072 indices required

	// used to keep track of which textures have been used per batch
	// evert time PushTexture is called, if the texture passed in does not exist
	// it is added. If the size of m_activeTextures exceeds m_maxTextures, ShouldFlush()
	// will return true
	Texture *m_activeTextures[5];

	// refers to the shader program used for this sprite batch
    unsigned int m_shader;
	unsigned int m_uniformTextureLoc;

	// vertex array object, vertex buffer object and index buffer object
	// used for openGL rendering
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ibo;

	// refers to the currentTextureID
	// used to calculate the which glActiveTexture( GL_TEXTURE0 + m_currentTextureID )
	// incromented when a unique texture is passed to PushTexture(...)
    unsigned int m_currentTextureID;

	// constant arbitary number
	// our shader supports 5 sampler2D objects
    unsigned int m_maxTextures;

	int m_numFlushes;

private:

	// this function returns a new position that has been rotated around the origion.
	// glm::vec2 RotateAround(glm::vec2 Position, float rotation);

	unsigned int	LoadShader(const char* a_filename, unsigned int a_type);

	unsigned int	CreateProgram(unsigned int a_vertexShader, unsigned int a_controlShader, unsigned int a_evaluationShader, unsigned int a_geometryShader, unsigned int a_fragmentShader,
									  unsigned int a_inputAttributeCount = 0, const char** a_inputAttributes = 0,
									  unsigned int a_outputAttributeCount = 0, const char** a_outputAttributes = 0);

	void GetOrtho(float *mat4x4, float left, float right, float bottom, float top, float a_fNear, float a_fFar)
	{
		
		mat4x4[0] = 2.0f / (right - left);;
		mat4x4[1] = 0.0f;
		mat4x4[2] = 0.0f;
		mat4x4[3] = 0.0f;

		mat4x4[4] = 0.0f;
		mat4x4[5] = 2.0f / (top - bottom);
		mat4x4[6] = 0.0f;
		mat4x4[7] = 0.0f;
		
		mat4x4[8] = 0.0f;
		mat4x4[9] = 0.0f;
		mat4x4[10] = 2.0f / (a_fFar - a_fNear);
		mat4x4[11] = 0.0f;

		mat4x4[12] = -1.0f * ((right + left) / (right - left));
		mat4x4[13] = -1.0f * ((top + bottom) / (top - bottom));
		mat4x4[14] = -1.0f * ((a_fFar + a_fNear) / (a_fFar - a_fNear));
		mat4x4[15] = 1.0f;
	}

	// helper function for loading shader code into memory
	unsigned char*	FileToBuffer(const char* a_szPath);

};

#endif