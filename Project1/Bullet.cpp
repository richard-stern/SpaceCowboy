#include "Bullet.h"

Bullet::Bullet(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision) : GameObject( szTexturePath, v2Pos, eCollision )
{
}

Bullet::~Bullet()
{
}

void Bullet::Update(float fDeltaTime)
{
}

void Bullet::Shoot(Vector2 v2StartPos, Vector2 v2Dir)
{
}