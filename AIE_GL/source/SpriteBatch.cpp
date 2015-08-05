#include "SpriteBatch.h"
#include "SpriteBatch_GL3.h"
#include "Application.h"
#include "Texture.h"
#include <assert.h>

SpriteBatch *SpriteBatch::Factory::Create(Application *pApp, ERenderMode mode)
{
	if( mode == GL3 )
	{
		return new SpriteBatch_GL3(pApp);
	}

	assert(false && "No available Sprite Batch Implementation");
	return nullptr;
}

void SpriteBatch::Factory::Destroy(SpriteBatch *pSpriteBatch)
{
	delete pSpriteBatch;
}

SpriteBatch::SpriteBatch(Application *pApp)
{
	m_pApplication = pApp;
	SetRenderColor(255,255,255,255);
	SetUVRect(0.0f, 0.0f, 1.0f, 1.0f);
	unsigned int pixels[1] = {0xFFFFFFFF};
	m_nullTexture = new Texture(1,1, pixels);
	m_transformColumnMajor = false;
}

SpriteBatch::~SpriteBatch()
{
	delete m_nullTexture;
}

void SpriteBatch::SetRenderColor(unsigned int col)
{
	m_r = ((col & 0xFF000000) >> 24 );
	m_g = ((col & 0x00FF0000) >> 16);
	m_b = ((col & 0x0000FF00) >> 8 );
	m_a = ((col & 0x000000FF) >> 0 );
}

void SpriteBatch::SetRenderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_r = r;
	m_b = b;
	m_g = g;
	m_a = a;
}

void SpriteBatch::SetUVRect(float uvX, float uvY, float uvW, float uvH)
{
	m_uvX = uvX;
	m_uvY = uvY;
	m_uvW = uvW;
	m_uvH = uvH;
}

void SpriteBatch::SetColumnMajor(bool columnMajor)
{
	m_transformColumnMajor = columnMajor;
}

void SpriteBatch::SetCameraPos(float x, float y)
{
	m_fCameraX = x;
	m_fCameraY = y;
}

void SpriteBatch::GetCameraPos(float* outX, float* outY)
{
	*outX = m_fCameraX;
	*outY = m_fCameraY;
}

void SpriteBatch::GetViewRect(float* outMinX, float* outMinY, float* outMaxX, float* outMaxY)
{
	float width = (float)m_pApplication->GetViewWidth();
	float height = (float)m_pApplication->GetViewHeight();

	*outMinX = m_fCameraX - (width * 0.5f);
	*outMinY = m_fCameraY - (height * 0.5f);
	*outMaxX = m_fCameraX + (width * 0.5f);
	*outMaxY = m_fCameraY + (height * 0.5f);
}
