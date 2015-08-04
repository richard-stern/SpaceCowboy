#include "Star.h"

Star::Star(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision) : GameObject( szTexturePath, v2Pos, eCollision )
{
	SetActive(true);
	SetVisible(true);
}

Star::~Star()
{
}
