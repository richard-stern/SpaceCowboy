#include "Rect.h"
#include "SpriteBatch.h"
#include "Engine.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "Boss Bullet.h"
#include "GameObject.h"

BossBullet::BossBullet(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision) : GameObject(szTexturePath, v2Pos, eCollision)
{
	m_eCollisionLayer = ECOLLISIONLAYER_BOSS;
}

BossBullet::~BossBullet()
{

}

void BossBullet::Update(float fDeltaTime)
{
	if (GetActive())
	{
		Vector2 position = GetPosition();
		Vector2 velocity = GetVelocity();
		position += velocity * fDeltaTime;
		SetPosition(position);
		RecalculateAABB();

		GameObject* other = nullptr;
		bool collision = CollisionManager::GetSingleton()->IsColliding(this, &other);

		if (collision && other->GetCollisionLayer() == ECOLLISIONLAYER_PLAYER)
		{
			other->SetHealth(GetHealth() - 30);
			SetActive(false);
		}

		Engine::GetSingleton()->GetSpriteBatch()->GetViewRect(&minX, &minY, &maxX, &maxY);
		if (position.x > maxX)
			SetActive(false);
		else if (position.x < minX)
			SetActive(false);
		else if (position.y > maxY)
			SetActive(false);
		else if (position.y < minY)
			SetActive(false);
	}
	return;
}

void BossBullet::Shoot(Vector2 v2StartPos, Vector2 v2Dir)
{
	m_v2Pos = v2StartPos;
	m_v2Facing = v2Dir;
	m_v2Velocity = Vector2(10, 10);
	SetActive(true);
}


