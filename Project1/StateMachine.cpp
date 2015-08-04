#include "StateMachine.h"
#include "SpriteBatch.h"
#include "BaseState.h"
#include "MenuState.h"
#include "GameState.h"
//#include "PauseState.h"
#include "GameOverState.h"

StateMachine::StateMachine()
{
	//Set current state to the menu
	m_eCurrentState = ESTATE_MENU;

	//State
	StatesArray[ESTATE_MENU] = new MenuState();
	StatesArray[ESTATE_GAME] = new GameState();
	//StatesArray[ESTATE_PAUSED] = new PauseState();
	StatesArray[ESTATE_GAMEOVER] = new GameOverState();
}

StateMachine::~StateMachine()
{
	for (int i = 0; i < ESTATE_COUNT; i++)
	{
		delete StatesArray[i];
	}
}

void StateMachine::Update(float fDeltaTime)
{
	StatesArray[m_eCurrentState]->Update(this, fDeltaTime);
}

void StateMachine::Draw(SpriteBatch* pSpriteBatch)
{
	StatesArray[m_eCurrentState]->Draw(pSpriteBatch);
}

void StateMachine::ChangeState(EState eState)
{
	StatesArray[m_eCurrentState]->Exit();
	m_eCurrentState = eState;
	StatesArray[m_eCurrentState]->Enter();
}