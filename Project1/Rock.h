#pragma once

#include "GameObject.h"

class Rock : public GameObject
{
public:
	Rock(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision);
	~Rock();

	void Update(float fDeltaTime);

	float minX;
	float maxX;
	float minY;
	float maxY;
private:
	void Initialise();
};

