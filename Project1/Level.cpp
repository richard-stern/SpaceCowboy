#include "Level.h"
#include "Rock.h"
#include "Star.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include <stdlib.h>
#include "Engine.h"
#include "Application.h"

Level::Level()
{
	for (int i = 0; i < 20; i++)
	{
		m_v2EachPos.x = (float)(rand() % Engine::GetSingleton()->GetApplication()->GetWindowWidth() * 4);
		m_v2EachPos.x = (float)(rand() % Engine::GetSingleton()->GetApplication()->GetWindowHeight() * 4);
		rockStorage[i] = new Rock("rock_large.png", m_v2EachPos, ECOLLISIONTYPE_CIRCLE_MIN);
	}
	for (int i = 0; i < 20; i++)
	{
		m_v2EachPos.x = (float)(rand() % Engine::GetSingleton()->GetApplication()->GetWindowWidth());
		m_v2EachPos.x = (float)(rand() % Engine::GetSingleton()->GetApplication()->GetWindowHeight());
		starStorage[i] = new Star("star.png", m_v2EachPos, ECOLLISIONTYPE_NONE);
	}
}

Level::~Level()
{
	for (int i = 0; i < 20; i++)
	{
		delete rockStorage[i];
		delete starStorage[i];
	}
}

void Level::Update(float fDeltaTime)
{
	for (int i = 0; i < 20; i++)
	{
		if (rockStorage[i]->GetVisible())
		rockStorage[i]->Update(fDeltaTime);

		if (starStorage[i]->GetVisible())
		starStorage[i]->Update(fDeltaTime);
	}
}

void Level::Draw(SpriteBatch* pSpriteBatch)
{
	for (int i = 0; i < 20; i++)
	{
		if (rockStorage[i]->GetVisible() && rockStorage[i]->GetActive())
		{
			rockStorage[i]->Draw(pSpriteBatch);
		}
		if (starStorage[i]->GetVisible() && starStorage[i]->GetActive())
		{
			starStorage[i]->Draw(pSpriteBatch);
		}
	}
}