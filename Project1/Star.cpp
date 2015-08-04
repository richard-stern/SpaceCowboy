#include "Star.h"

Star::Star(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision) : GameObject( szTexturePath, v2Pos, eCollision )
{
	SetActive(true);
	SetVisible(true);

	m_rAABB.min = v2Pos;
	m_rAABB.max = v2Pos + Vector2(8, 8);
}

Star::~Star()
{
}
