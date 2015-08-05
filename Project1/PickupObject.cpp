#include "PickupObject.h"

#include "CollisionManager.h"


PickupObject::PickupObject(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision)
	: GameObject(szTexturePath, v2Pos, eCollision)
{
	m_eCollisionLayer = ECOLLISIONLAYER_ROCK;
	CollisionManager::GetSingleton()->AddObject(this);
}


PickupObject::~PickupObject()
{
}

void PickupObject::Update(float fDeltaTime)
{
	GameObject* other = nullptr;
	bool collision = CollisionManager::GetSingleton()->IsColliding(this, &other);

	if (collision && other)
	{
		ApplyPowerUp((Player*)other);
	}
}

void PickupObject::ApplyPowerUp(Player* player)
{
	//Inherited classes add code here
}
