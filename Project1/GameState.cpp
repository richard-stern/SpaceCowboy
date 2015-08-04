#include "GameState.h"
#include "SpriteBatch.h"
#include "StateMachine.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "GUI.h"
#include "Engine.h"

GameState::GameState()
{
	GUI::CreateSingleton();
	m_v2PlayerOrigin.x = 400;
	m_v2PlayerOrigin.y = 500;
}

GameState::~GameState()
{
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

	//Player Death
	if (m_pPlayer->GetHealth() == 0)
	{
		pStateMachine->ChangeState(ESTATE_GAMEOVER);
	}

	//Menu return
	if (Input::GetSingleton()->WasKeyPressed(GLFW_KEY_F1))
	{
		pStateMachine->ChangeState(ESTATE_MENU);
	}

	//Pause State
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_ESCAPE) || Input::GetSingleton()->IsKeyDown(GLFW_KEY_P))
	{
		pStateMachine->ChangeState(ESTATE_PAUSED);
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
	m_pPlayer = nullptr;
	delete m_pLevel;
	m_pLevel = nullptr;

	Engine::GetSingleton()->GetSpriteBatch()->SetCameraPos(0, 0);
}