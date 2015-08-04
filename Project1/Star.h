#pragma once

#include "GameObject.h"

class Star : public GameObject
{
public:
	Star(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision);
	~Star();
};

