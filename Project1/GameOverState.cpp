#include "GameOverState.h"
#include "StateMachine.h"
#include "SpriteBatch.h"
#include "Font.h"
#include "Input.h"
#include "Engine.h"
#include "Application.h"
#include "GUI.h"
#include "Game.h"
#include "Texture.h"

GameOverState::GameOverState()
{
	m_font1 = new Font("./Fonts/ocr_a_100px.fnt");
	m_font2 = new Font("./Fonts/ocr_a_36px.fnt");

	m_background = new Texture("./Images/spaceship_explosion.png");
}

GameOverState::~GameOverState()
{
	delete m_font1;
	delete m_font2;

	delete m_background;
}

void GameOverState::Enter()
{
	
}

void GameOverState::Update(StateMachine* pStateMachine, float fDeltaTime)
{

	if (Input::GetSingleton()->WasKeyPressed('N'))
	{
		pStateMachine->ChangeState(ESTATE_GAME);
	}
	
	if (Input::GetSingleton()->WasKeyPressed('X'))
	{
		Engine::GetSingleton()->GetApplication()->Quit();
	}

	if (Input::GetSingleton()->WasKeyPressed('M'))
	{
		pStateMachine->ChangeState(ESTATE_MENU);
	}
}

void GameOverState::Draw(SpriteBatch* pSpriteBatch)
{
	int m_score = GUI::GetSingleton()->GetScore();

	char scoreArray[25];

	sprintf_s(scoreArray, 25, "Player Score: %d", m_score);

	pSpriteBatch->DrawSprite(m_background, 616, 439, 1232, 878);

	pSpriteBatch->DrawString(m_font1, "GAME OVER", 325, 100);

	pSpriteBatch->DrawString(m_font2, scoreArray, 400, 300);

	pSpriteBatch->DrawString(m_font2, "press N to start a new game, or press X to exit", 120, 800);
	pSpriteBatch->DrawString(m_font2, "Press M to go back to the main menu,", 240, 750);
}

void GameOverState::Exit()
{
	
}