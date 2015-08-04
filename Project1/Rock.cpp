#include <stdlib.h>
#include "GUI.h"
#include "Engine.h"
#include "Application.h"
#include "SpriteBatch.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Rock.h"

Rock::Rock(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision) : GameObject( szTexturePath, v2Pos, eCollision )
{
	SetVelocity(Vector2((float)(10), (float)(10)));
	m_eCollisionLayer = ECOLLISIONLAYER_ALL;
	SetHealth(233);
	SetActive(true);
	SetVisible(true);
	CollisionManager::GetSingleton()->AddObject(this);
}

Rock::~Rock()
{
}

void Rock::Update(float fDeltaTime)
{
	if (GetActive())
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

		Engine::GetSingleton()->GetSpriteBatch()->GetViewRect(&minX, &minY, &maxX, &maxY);
		if (position.x > maxX)
			SetVisible(false);
		else if (position.x < minX)
			SetVisible(false);
		else if (position.y > maxY)
			SetVisible(false);
		else if (position.y < minY)
			SetVisible(false);
	}
	return;
}