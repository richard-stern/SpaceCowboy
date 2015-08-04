#pragma once

#include "PickupObject.h"

class PickupHealth :
	public PickupObject
{
public:
	PickupHealth(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision, float Strength = 100.0f);
	virtual ~PickupHealth();

	void ApplyPowerUp(Player* player);

private:
	float m_strength;
};

