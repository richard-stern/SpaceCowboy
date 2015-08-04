#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision);
	virtual ~Bullet();

	void Update(float fDeltaTime);

	//Specify the bullets start point and direction to fly when it gets shot.
	void Shoot(Vector2 v2StartPos, Vector2 v2Dir);

};

