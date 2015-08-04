#include "PickupHealth.h"

#include "Player.h"


PickupHealth::PickupHealth(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision, float Strength)
	: PickupObject(szTexturePath, v2Pos, eCollision)
{
	m_strength = Strength;
}


PickupHealth::~PickupHealth()
{
}

void PickupHealth::ApplyPowerUp(Player* player)
{
	float healthBoost = player->GetHealth() + m_strength;
	float healthMax = player->GetMaxHealth();

	//add shield
	if (healthBoost < healthMax)
	{
		player->SetHealth(healthBoost);
	}
	else
	{
		player->SetHealth(player->GetMaxHealth());
	}

	//make pickup disappear
	SetVisible(false);
	SetActive(false);
}