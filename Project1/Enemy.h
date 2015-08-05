#pragma once
#include "GameObject.h"

class Texture; 
class Vector2; 
class BulletManager; 

class Enemy : public GameObject
{
public:
	Enemy(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision, GameObject* pPlayer);
	~Enemy();

	void Update(float fDeltaTime); 

	void Seek(); //used for finding the player 
	

private: 
	BulletManager* m_pBulletManager;
	GameObject* m_pPlayer; 

};

