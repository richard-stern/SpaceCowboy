#include "BulletManager.h"
#include "Bullet.h"
#include "CollisionManager.h"
#include "TextureManager.h"
BulletManager::BulletManager()
{
	Vector2 empty(0,0);
	for (int i = 0; i < 100; i++)
	{
		bulletList[i] = new Bullet("nodeTexture.png", empty, ECOLLISIONTYPE_CIRCLE_MIN);
	}
}

BulletManager::~BulletManager()
{
	for (int i = 0; i < 100; i++)
	{
			delete bulletList[i];
	}
}

void BulletManager::Update(float fDeltaTime)
{
	for (int i = 0; i < 100;  i++)
	{
		if (bulletList[i]->GetActive())
		{
			bulletList[i]->Update(fDeltaTime);
		}
	}
}

void BulletManager::Draw(SpriteBatch* pSpritebatch)
{
	for (int i = 0; i < 100; i++)
	{
		if (bulletList[i]->GetActive())
		{
			bulletList[i]->Draw(pSpritebatch);
		}
	}
}

void BulletManager::ShootBullet(Vector2 v2StartPos, Vector2 v2Dir)
{
	for (int i = 0; i < 100; i++)
	{
		if (!bulletList[i]->GetActive())
		{
			bulletList[i]->Shoot(v2StartPos, v2Dir);
		}
	}
}