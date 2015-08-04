#pragma once

#include "GameObject.h"

class BossBullet : public GameObject
{
public:
	
	BossBullet(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision);
	virtual ~BossBullet();

	void Update(float fDeltaTime);

	void Shoot(Vector2 v2StartPos, Vector2 v2Dir);

private:
	float minX;
	float maxX;
	float minY;
	float maxY;
};

