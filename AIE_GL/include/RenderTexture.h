#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#include "Texture.h"

class RenderTexture : public Texture
{
public:

	RenderTexture(unsigned int width, unsigned int height);
	virtual ~RenderTexture();

	unsigned int GetFrameBufferHandle();

protected:
private:

	unsigned int m_fbo;
	unsigned int m_rbo;

};

#endif