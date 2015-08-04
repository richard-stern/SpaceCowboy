#include "Level.h"
#include "Rock.h"
#include "Star.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include <stdlib.h>
#include "Engine.h"
#include "Application.h"

#define ROCK_COUNT 20
#define STAR_COUNT 20

Level::Level()
{
	unsigned int windowWidth = Engine::GetSingleton()->GetApplication()->GetWindowWidth();
	unsigned int windowHeight = Engine::GetSingleton()->GetApplication()->GetWindowHeight();

	for (int i = 0; i < ROCK_COUNT; i++)
	{
		m_v2EachPos.x = (float)(rand() % windowWidth);
		m_v2EachPos.y = (float)(rand() % windowHeight);
		rockStorage[i] = new Rock("rock_large.png", m_v2EachPos, ECOLLISIONTYPE_CIRCLE_MIN);
	}

	for (int i = 0; i < STAR_COUNT; i++)
	{
		//Random Pos
		m_v2EachPos.x = (float)(rand() % windowWidth);
		m_v2EachPos.y = (float)(rand() % windowHeight);

		if (i / 5)
		{
			starStorage[i] = new Star("star.png", m_v2EachPos, ECOLLISIONTYPE_NONE);
			continue;
		}
		else if (i / 2)
		{
			starStorage[i] = new Star("agent.png", m_v2EachPos, ECOLLISIONTYPE_NONE);
			continue;
		}
		else
		{
			starStorage[i] = new Star("rock_small.png", m_v2EachPos, ECOLLISIONTYPE_NONE);
			continue;
		}
	}

	//------------------------------------------------------------------------------------------
	//To Do?
	//Storage[i] = new PickupShield("shieldPickup.png", m_v2EachPos, ECOLLISIONTYPE_AABB);
	//------------------------------------------------------------------------------------------
}

Level::~Level()
{
	for (int i = 0; i < ROCK_COUNT; i++)
	{
		delete rockStorage[i];
		
	}
	for (int i = 0; i < STAR_COUNT; i++)
	{
		delete starStorage[i];
	}
}

void Level::Update(float fDeltaTime)
{
	for (int i = 0; i < ROCK_COUNT; i++)
	{
		if (rockStorage[i]->GetVisible())
			rockStorage[i]->Update(fDeltaTime);
	}
	for (int i = 0; i < STAR_COUNT; i++)
	{
		if (starStorage[i]->GetVisible())
		starStorage[i]->Update(fDeltaTime);
	}
}

void Level::Draw(SpriteBatch* pSpriteBatch)
{
	for (int i = 0; i < ROCK_COUNT; i++)
	{
		rockStorage[i]->Draw(pSpriteBatch);
		
	}
	for (int i = 0; i < STAR_COUNT; i++)
	{

		starStorage[i]->Draw(pSpriteBatch);
	}
}