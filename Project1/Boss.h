#pragma once
#include "Application.h"
#include "GameObject.h"

class BulletManager;

class Boss : public GameObject
{
public:
	Boss(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision);
	virtual ~Boss();

	//TODO: add rotating mini cat enemies

		//fill the screen with lead
	void fireAllTheBullets();
	 //update the cat
	void Update(float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch, int score);
	int GetBossHealth();
	
	Vector2 m_Size;
	BulletManager* m_pBulletManager;
	Texture* m_pBoss;
	
	GameObject* m_pCollider;

	int m_Health = 100;
	int m_WindowWidth;
	int m_WindowHeight;
};
