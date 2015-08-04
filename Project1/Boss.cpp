#include "Boss.h"
#include "SpriteBatch.h"
#include "TextureManager.h"
#include "Texture.h"
#include "glfw3.h"
#include "BulletManager.h"
#include <math.h>
#include "Application.h"
#include "Engine.h"
#include "CollisionManager.h"
#include "GUI.h"

Boss::Boss(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision) : GameObject(szTexturePath, v2Pos, eCollision)
{
	//create new bullets for cat
		m_pBulletManager = new BulletManager();

		//get the cat texture
		m_pBoss = TextureManager::GetSingleton()->LoadTexture("CAT BOSS.png");

		//set pos
		SetPosition(v2Pos);
		m_Size = Vector2(209, 298);
		
		//ini the hp
		m_Health = 10000;

		m_WindowWidth = 0;
		m_WindowHeight = 0;

		//??
		m_pCollider = nullptr;
	}

Boss::~Boss()
{
	delete m_pBulletManager;
}

void Boss::Update(float fDeltaTime)
{
	//get window size
	if (m_WindowWidth == 0)
	{
		m_WindowWidth = Engine::GetSingleton()->GetApplication()->GetWindowWidth();
		m_WindowHeight = Engine::GetSingleton()->GetApplication()->GetWindowHeight();
	}

	m_pCollider = nullptr;

	//col manage, boss ignores unit collusion so remove?
	//if (CollisionManager::GetSingleton()->IsColliding(this, &m_pCollider))
	//{
	//	SetVelocity(m_pCollider->GetVelocity());
	//		m_Health -= 20 + rand() % 20;
	//}

}

void Boss::Draw(SpriteBatch* pSpriteBatch, int score)
{
	//draw the cat after a certain score
	pSpriteBatch->DrawSprite(m_pBoss, GetPosition().x, GetPosition().y, m_Size.x, m_Size.y);

}

int Boss::GetBossHealth()
{
	//function to pass cat hp
	return (int)m_Health;
}

