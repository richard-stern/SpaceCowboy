#pragma once

#include "Vector2.h"

class SpriteBatch;
class BossBullet;

class BossBulletManager
{
public:
	BossBulletManager();
	~BossBulletManager();

	void Update(float fDeltaTime);
	void Draw(SpriteBatch* pSpritebatch);

	//Shoot out a bullet
	//v2StartPos: The start pos for the bullet
	//v2Dir: the direction to shoot the bullet as a normalised vector
	void ShootBullet(Vector2 v2StartPos, Vector2 v2Dir);

private:
	BossBullet* bulletList[100];
};

