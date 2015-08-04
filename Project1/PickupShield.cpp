#include "PickupShield.h"

#include "Player.h"


PickupShield::PickupShield(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision, float Strength)
	: PickupObject(szTexturePath, v2Pos, eCollision)
{
	m_strength = Strength;
}


PickupShield::~PickupShield()
{
}

void PickupShield::ApplyPowerUp(Player* player)
{
	float shieldBoost = player->GetPlayerShield() + m_strength;
	float shieldMax = player->GetPlayerShieldMax();

	//add shield
	if (shieldBoost < shieldMax)
	{
		player->SetPlayerShield(shieldBoost);
	}
	else
	{
		player->SetPlayerShield(player->GetPlayerShieldMax());
	}

	//make pickup disappear
	SetVisible(false);
	SetActive(false);
}


