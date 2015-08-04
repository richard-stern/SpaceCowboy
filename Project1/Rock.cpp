#include <stdlib.h>
#include "GUI.h"
#include "Engine.h"
#include "Application.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Rock.h"

Rock::Rock(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision) : GameObject( szTexturePath, v2Pos, eCollision )
{
	SetVelocity(Vector2((float)(rand() % 300 - 150), (float)(rand() % 300 - 150)));
	m_eCollisionLayer = ECOLLISIONLAYER_ALL;
	SetHealth(226);
	SetActive(true);
	CollisionManager::GetSingleton()->AddObject(this);
}

Rock::~Rock()
{
}

void Rock::Update(float fDeltaTime)
{
	// retrieve current posotion and velocity
	Vector2 position = GetPosition();
	Vector2 velocity = GetVelocity();

	// add current velocity to position and set
	position += velocity * fDeltaTime;
	SetPosition(position);
	RecalculateAABB();

	GameObject* other = nullptr;
	bool collision = CollisionManager::GetSingleton()->IsColliding(this, &other);

	if (collision && other)
	{
		Vector2 temp = GetVelocity();
		SetVelocity(other->GetVelocity());
		other->SetVelocity(temp);
	}

	if (GetHealth() <= 0)
	{
		GUI::GetSingleton()->AddScore(100);
		SetActive(false);
	}

	return;
}