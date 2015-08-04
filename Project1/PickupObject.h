#pragma once

#include "GameObject.h"

class Texture;
class Player;

class PickupObject :
	public GameObject
{
public:
	PickupObject(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision);
	virtual ~PickupObject();

	void Update(float fDeltaTime);

	virtual void ApplyPowerUp(Player* player);

};

