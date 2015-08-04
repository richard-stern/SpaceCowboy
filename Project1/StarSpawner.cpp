#include "StarSpawner.h"
#include "Star.h"
#include "Texture.h"
#include "TextureManager.h"
#include "SpriteBatch.h"
#include "CollisionManager.h"
#include <stdlib.h>

//-------------------------------------------------------------------
// Overloaded Construtor
//-------------------------------------------------------------------
//
// Param:
//		nScreenWidth: The Game ScreenWidth
//-------------------------------------------------------------------
StarSpawner::StarSpawner(int nScreenWidth, int nScreenHeight)
{
	//Variables
	m_nStarCount = 0;
	m_fStarSpawnTimer = 0.0f;
	m_nScreenWidth = nScreenWidth;
	m_nScreenHeight = nScreenHeight;

	//char* 	// Textures used
	m_cpStar1 = "./Images/invaders/invaders_1_00.png";
	m_cpStar2 = "./Images/invaders/invaders_6_00.png";
	m_cpStar3 = "./Images/nodeTexture.png";

	for (int i = 0; i < MAX_STARS; ++i)
	{
		if (i / 5)
			m_pcStarTexture = m_cpStar1;

		else if (i / 2)
			m_pcStarTexture = m_cpStar2;

		else
			m_pcStarTexture = m_cpStar3;

		//Default pos to 0.
		Vector2 Zero;
		Zero.x = (float)(rand() % m_nScreenWidth);
		Zero.y = (float)(rand() % m_nScreenHeight);

		m_apStarList[i] = new Star(m_pcStarTexture, Zero, ECOLLISIONTYPE_NONE);
	}
}

//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
StarSpawner::~StarSpawner()
{
	for (int i = 0; i < MAX_STARS; ++i)
	{
		delete m_apStarList[i];
	}
}

//-------------------------------------------------------------------
// Update Function
//-------------------------------------------------------------------
//
// Param:
//		fDeltaTime: DeltaTime/ time in seconds passed
//-------------------------------------------------------------------
void StarSpawner::Update(float fDeltaTime)
{
	m_fStarSpawnTimer += fDeltaTime;
	if (m_fStarSpawnTimer >= SPAWN_DELAY)
	{
		float spawnPos = (float)(rand() % m_nScreenWidth);
		m_apStarList[m_nStarCount]->Spawn(spawnPos, -20.0f);
		++m_nStarCount;

		if (m_nStarCount >= MAX_STARS)
			m_nStarCount = 0;

		m_fStarSpawnTimer = 0.0f;
	}

	for (int i = 0; i < MAX_STARS; ++i)
	{
		m_apStarList[i]->Update(fDeltaTime);
	}
}

//-------------------------------------------------------------------
// Draw
//-------------------------------------------------------------------
//
// Param:
//		pSpritebatch: a SpriteBatch.
//-------------------------------------------------------------------
void StarSpawner::Draw(SpriteBatch* pSpriteBatch)
{
	for (int i = 0; i < MAX_STARS; ++i)
	{
		if (i / 5)
			pSpriteBatch->SetRenderColor(255, 255, 255, 255 * (unsigned char)(1.0f - m_fStarSpawnTimer));

		else if (i / 2)
			pSpriteBatch->SetRenderColor(204, 204, 255, 255);

		else
			pSpriteBatch->SetRenderColor(112, 112, 153, 255);

		m_apStarList[i]->Draw(pSpriteBatch);
	}
}