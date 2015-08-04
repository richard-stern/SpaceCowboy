#include "Level.h"
#include "Rock.h"
#include "Star.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include <stdlib.h>
#include "Engine.h"
#include "Application.h"

#define ROCK_COUNT 20
#define STAR_COUNT 120
Level::Level()
{
	unsigned int windowWidth = Engine::GetSingleton()->GetApplication()->GetWindowWidth() * 4;
	unsigned int windowHeight = Engine::GetSingleton()->GetApplication()->GetWindowHeight() * 4;
	for (int i = 0; i < ROCK_COUNT; i++)
	{
		m_v2EachPos.x = (float)(rand() % windowWidth);
		m_v2EachPos.y = (float)(rand() % windowHeight);
		rockStorage[i] = new Rock("rock_large.png", m_v2EachPos, ECOLLISIONTYPE_CIRCLE_MIN);
	}
	for (int i = 0; i < STAR_COUNT; i++)
	{
		m_v2EachPos.x = (float)(rand() % windowWidth);
		m_v2EachPos.y = (float)(rand() % windowHeight);
		starStorage[i] = new Star("star.png", m_v2EachPos, ECOLLISIONTYPE_NONE);
	}
	
	//------------------------------------------------------------------------------------------
	//To Do?
	//Storage[i] = new PickupShield("shieldPickup.png", m_v2EachPos, ECOLLISIONTYPE_AABB);
	//------------------------------------------------------------------------------------------
}

Level::~Level()
{
	for (int i = 0; i < ROCK_COUNT; i++) //loop and delete asteroids(Rocks)
	{
		delete rockStorage[i];
	}
	for (int i = 0; i < STAR_COUNT; i++) // loop and delete stars 
	{
		delete starStorage[i];
	}
}

void Level::Update(float fDeltaTime)
{
	for (int i = 0; i < ROCK_COUNT; i++)
	{
			rockStorage[i]->Update(fDeltaTime);
	}
	for (int i = 0; i < STAR_COUNT; i++)
	{
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