#include "BossBulletManager.h"
#include "Boss Bullet.h"
#include "CollisionManager.h"
#include "TextureManager.h"

BossBulletManager::BossBulletManager()
{
	Vector2 empty(0, 0);
	for (int i = 0; i < 100; i++)
	{
		bulletList[i] = new BossBullet("nodeTexture2.png", empty, ECOLLISIONTYPE_CIRCLE_MIN);
	}
}

BossBulletManager::~BossBulletManager()
{
	for (int i = 0; i < 100; i++)
	{
		delete bulletList[i];
	}
}

void BossBulletManager::Update(float fDeltaTime)
{
	for (int i = 0; i < 100; i++)
	{
		if (bulletList[i]->GetActive())
		{
			bulletList[i]->Update(fDeltaTime);
		}
	}
}

void BossBulletManager::Draw(SpriteBatch* pSpritebatch)
{
	for (int i = 0; i < 100; i++)
	{
		if (bulletList[i]->GetActive())
		{
			bulletList[i]->Draw(pSpritebatch);
		}
	}
}

void BossBulletManager::ShootBullet(Vector2 v2StartPos, Vector2 v2Dir)
{
	for (int i = 0; i < 100; i++)
	{
		if (!bulletList[i]->GetActive())
		{
			bulletList[i]->Shoot(v2StartPos, v2Dir);
			break;
		}
	}
}



//void BossBullet::ShootTypeU(Vector2 v2StartPos, Vector2 v2Dir)
//{
//	m_v2Pos = v2StartPos;
//	m_v2Facing = v2Dir;
//	m_v2Velocity = Vector2(10, 10);
//	SetActive(true);
//}
//void BossBullet::ShootTypeD(Vector2 v2StartPos, Vector2 v2Dir)
//{
//	m_v2Pos = v2StartPos;
//	m_v2Facing = v2Dir;
//	m_v2Velocity = Vector2(10, 10);
//	SetActive(true);
//}
//void BossBullet::ShootTypeR(Vector2 v2StartPos, Vector2 v2Dir)
//{
//	m_v2Pos = v2StartPos;
//	m_v2Facing = v2Dir;
//	m_v2Velocity = Vector2(10, 10);
//	SetActive(true);
//}
//void BossBullet::ShootTypeL(Vector2 v2StartPos, Vector2 v2Dir)
//{
//	m_v2Pos = v2StartPos;
//	m_v2Facing = v2Dir;
//	m_v2Velocity = Vector2(10, 10);
//	SetActive(true);
//}
//
//
//void BossBullet::ShootTypeShotgun(Vector2 v2StartPos, Vector2 v2Dir)
//{
//	m_v2Pos = v2StartPos;
//	m_v2Facing = v2Dir;
//	m_v2Velocity = Vector2(20, 20);
//	SetActive(true);
//}
//void BossBullet::ShootTypeSpray(Vector2 v2StartPos, Vector2 v2Dir)
//{
//	m_v2Pos = v2StartPos;
//	m_v2Facing = v2Dir;
//	m_v2Velocity = Vector2(7, 7);
//	SetActive(true);
//}