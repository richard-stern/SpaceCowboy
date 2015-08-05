#include "Level.h"
#include "Rock.h"
#include "Star.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include <stdlib.h>
#include "Engine.h"
#include "Application.h"
#include "SpriteBatch.h"
#include "Texture.h"

Level::Level()
{
	//get the screen size and multiply by 2 to increase location used for spawning
	unsigned int windowWidth = Engine::GetSingleton()->GetApplication()->GetWindowWidth() * 2;
	unsigned int windowHeight = Engine::GetSingleton()->GetApplication()->GetWindowHeight() * 2;

	m_fTimeFade = 0.0f;

	//spawn rocks
	for (int i = 0; i < ROCK_COUNT; i++)
	{
		//spawnSide is it used to determine which side of the player to spawn the object on with a 50% change for each side.  
		int spawnSide = rand() % 2; 

		//randomise the spawn position
		m_v2EachPos.x = (float)(rand() % windowWidth);
		m_v2EachPos.y = (float)(rand() % windowHeight);

		//if spawnSide == 0 it will multiply the spawn pos by -1 to make the position negative (behind the player)
		if (spawnSide == 0)
			m_v2EachPos *= -1; 

		//store the rock in an array, passing in texture pathm, position and collision type
		rockStorage[i] = new Rock("rock_large.png", m_v2EachPos, ECOLLISIONTYPE_CIRCLE_MIN);
	}

	//spawn stars
	for (int i = 0; i < STAR_COUNT; i++)
	{
		//spawnSide is it used to determine which side of the player to spawn the object on with a 50% change for each side.  
		int spawnSide = rand() % 2;

		//randomise the spawn position
		m_v2EachPos.x = (float)(rand() % windowWidth);
		m_v2EachPos.y = (float)(rand() % windowHeight);

		//if spawnSide == 0 it will multiply the spawn pos by -1 to make the position negative (behind the player)
		if (spawnSide == 0)
			m_v2EachPos *= -1;

		star = new Star("star1.png", m_v2EachPos, ECOLLISIONTYPE_NONE);
		star1 = new Star("star.png", m_v2EachPos, ECOLLISIONTYPE_NONE);;

		//make every 5th star a different texture 
		if (i % 5)
		{
			starStorage[i] = star;
			continue;
		}
		else
		{
			starStorage[i] = star1;
			continue;
		}
	}
	
	//------------------------------------------------------------------------------------------
	//To Do?
	//Storage[i] = new PickupShield("shieldPickup.png", m_v2EachPos, ECOLLISIONTYPE_CIRCLE_MIN);
	//Storage[i] = new PickupHealth("healthPickup.png", m_v2EachPos, ECOLLISIONTYPE_CIRCLE_MIN); 
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
	//update the rocks 
	for (int i = 0; i < ROCK_COUNT; i++)
	{
			rockStorage[i]->Update(fDeltaTime);
	}
	//update the stars
	for (int i = 0; i < STAR_COUNT; i++)
	{
		starStorage[i]->Update(fDeltaTime);
	}

	//Colour Fade
	m_fTimeFade += fDeltaTime;
	if (m_fTimeFade > 6.0f)
	{
		m_fTimeFade = 0.0f;
		//m_bIsActive = false;
	}
}

void Level::Draw(SpriteBatch* pSpriteBatch)
{
	//draw the stars 
	for (int i = 0; i < STAR_COUNT; i++)
	{
		//White Star
		if (i / 3) {
			pSpriteBatch->SetRenderColor(255, 255, 255, 255 * (unsigned char)(1.0f + m_fTimeFade));
		}
		//Grey Star
		else if (i / 7) {
			pSpriteBatch->SetRenderColor(178, 178, 178, 255 * (unsigned char)(1.0f - m_fTimeFade));
		}
		//Full Star
		else {
			pSpriteBatch->SetRenderColor(255, 255, 255, 255);
		}

		starStorage[i]->Draw(pSpriteBatch);
	}
	//draw the rocks
	for (int i = 0; i < ROCK_COUNT; i++)
	{
		rockStorage[i]->Draw(pSpriteBatch);
	}
}