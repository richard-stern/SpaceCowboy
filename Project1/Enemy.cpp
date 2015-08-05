#include "Enemy.h"
#include "BulletManager.h"
#include "CollisionManager.h"

Enemy::Enemy(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision, GameObject* pPlayer) : GameObject(szTexturePath, v2Pos, eCollision)
{
	//initialise the position and health variables 
	m_v2Pos = v2Pos; 
	m_nHealth = 100; 
	m_nMaxHealth = 100; 
	m_bActive = true; 

	//set the collision layer 
	SetCollisionLayer(ECOLLISIONLAYER_ALL); 

	//set the pointer to the player object
	m_pPlayer = pPlayer; 


	//create a bullet manager for the specific enemy
	m_pBulletManager = new BulletManager(); 



}


Enemy::~Enemy()
{
	//delete and set the bullet manager pointer to null 
	delete m_pBulletManager; 
	m_pBulletManager = nullptr; 
}


void Enemy::Update(float fDeltaTime)
{
	if (m_nHealth >= 30)
	{
		Seek();
	}
}


void Enemy::Seek()
{

}


