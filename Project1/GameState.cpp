#include "GameState.h"
#include "SpriteBatch.h"
#include "StateMachine.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "GUI.h"

GameState::GameState()
{
	Enter();

	GUI::CreateSingleton();

	m_v2PlayerOrigin.x = 400;
	m_v2PlayerOrigin.y = 500;
}

GameState::~GameState()
{
	delete m_pPlayer;
	delete m_pLevel;
	GUI::DestroySingleton();
}

void GameState::Enter()
{
	m_pLevel = new Level();
	m_pPlayer = new Player("player.png", m_v2PlayerOrigin, ECOLLISIONTYPE_AABB);
}

void GameState::Update(StateMachine* pStateMachine, float fDeltaTime)
{
	m_pLevel->Update(fDeltaTime);

	m_pPlayer->Update(fDeltaTime);

	if (m_pPlayer->GetHealth() == 0)
	{
		pStateMachine->ChangeState(ESTATE_GAMEOVER);
	}
}

void GameState::Draw(SpriteBatch* pSpriteBatch)
{
	Vector2 playerPos = m_pPlayer->GetPosition();

	m_pLevel->Draw(pSpriteBatch);

	m_pPlayer->Draw(pSpriteBatch);

	pSpriteBatch->SetCameraPos(playerPos.x, playerPos.y);

	//GUI Draw and parameters
	float myVar = (float)m_pPlayer->GetPlayerHealthScaled();
	
	GUI::GetSingleton()->Draw(pSpriteBatch, myVar);
}

void GameState::Exit()
{
	delete m_pPlayer;
	delete m_pLevel;
}