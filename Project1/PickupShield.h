#pragma once

#include "PickupObject.h"

class PickupShield :
	public PickupObject
{
public:
	PickupShield(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision, float Strength = 100.0f);
	virtual ~PickupShield();

	void ApplyPowerUp(Player* player);

private:
	float m_strength;
};

