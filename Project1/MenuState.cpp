#include "MenuState.h"
#include "StateMachine.h"
#include "SpriteBatch.h"
#include "TextureManager.h"
#include <iostream>
#include <string>
#include "Application.h"
#include "Engine.h"
#include "Input.h"
#include "BaseState.h"

MenuState::MenuState()
{
	m_WindowWidth = 0;
	m_WindowHeight = 0;

	m_pSpaceShipTexture = TextureManager::GetSingleton()->LoadTexture("player.png");
	m_pBackgroundLayer1 = TextureManager::GetSingleton()->LoadTexture("MainMenuPage.png");
	m_pBackgroundLayer2 = TextureManager::GetSingleton()->LoadTexture("MainMenuPage2.png");
	m_pDogeTexture = TextureManager::GetSingleton()->LoadTexture("Doge.png");
	
	for (int i = 0; i < 30; i++)
	{
		std::string fileName = "GunSprite/GunSprite_";
		if (i == 27)
		{
			fileName += "0002";
		}
		else if (i == 28)
		{
			fileName += "0002";
		}
		else if (i == 29)
		{
			fileName += "0001";
		}
		else
		{
			if (i < 10)
			{

				fileName += "000";
				fileName += std::to_string(i);
			}
			else
			{
				fileName += "00";
				fileName += std::to_string(i);
			}
		}
		fileName += "_g.png";
		char* tempFileName = (char*)fileName.c_str();
		m_pGunSprite[i] = TextureManager::GetSingleton()->LoadTexture(tempFileName);
	}
	m_BtnPos[0] = Vector2(0, 0);

	m_SpaceShipAcc = Vector2(0,0);
	m_SpaceShipVel = Vector2(0, 0);
	m_SpaceShipPos = Vector2(0, 0);

	m_GunPos = Vector2(0, 0);

	m_DogePos = Vector2(0, 0);

	m_Playing = false;
	m_Frame = 0;
	m_TimerMax = 0.03333f;
	m_Timer = m_TimerMax;
	m_startGame = false;
}

MenuState::~MenuState()
{
}

void MenuState::Enter()
{
	m_Playing = false;
	m_startGame = false;
}

void MenuState::Update(StateMachine* pStateMachine, float fDeltaTime)
{
	if (m_WindowWidth == 0)
	{
		m_WindowWidth = Engine::GetSingleton()->GetApplication()->GetWindowWidth();
		m_WindowHeight = Engine::GetSingleton()->GetApplication()->GetWindowHeight();

		m_BtnPos[0] = Vector2(m_WindowWidth / 8.5f, m_WindowHeight / 2.1f);
		m_SpaceShipPos = Vector2(m_WindowWidth - m_WindowWidth / 5, m_WindowHeight - 200);
		m_DogePos = Vector2(m_WindowWidth + m_WindowWidth / 5, m_WindowHeight - 200);
	}
	//Button Logic
	int MouseX = Input::GetSingleton()->GetMouseX();
	int MouseY = Input::GetSingleton()->GetMouseY();
	if (Input::GetSingleton()->IsMouseButtonDown(0))
	{
		if (MouseX > m_BtnPos[0].x && MouseX < m_BtnPos[0].x + 400 &&
			MouseY > m_BtnPos[0].y && MouseY < m_BtnPos[0].y + 100)
		{
			m_Playing = true;
		}
	}

	if (m_Frame >= 29)
	{
		m_Playing = false;
		m_Timer = m_TimerMax;
		m_Frame = 0;
	}
	if (m_Playing == true)
	{
		m_startGame = true;
		m_SpaceShipVel = Vector2(0, -0.04f);
		if (m_Timer <= 0)
		{
			if (m_Frame == 6)
				m_Timer = m_TimerMax * 10;
			else
				m_Timer = m_TimerMax;
			m_Frame += 1;
		}
		m_Timer -= fDeltaTime;
	}


	m_SpaceShipPos += m_SpaceShipVel;
	if (m_startGame == true)
	{
		if (m_DogePos.x > m_WindowWidth - 90)
			m_DogePos.x -= 0.06f;

		if (m_SpaceShipPos.y < -100)
			pStateMachine->ChangeState(ESTATE_GAME);
	}
}

void MenuState::Draw(SpriteBatch* pSpriteBatch)
{
	pSpriteBatch->DrawSprite(m_pBackgroundLayer2, (float)m_WindowWidth / 2, (float)m_WindowHeight / 2, (float)m_WindowWidth, (float)m_WindowHeight);
	//SpaceShip HERE
	pSpriteBatch->SetRenderColor(0x0000FFFF);
	pSpriteBatch->DrawSprite(m_pSpaceShipTexture, m_SpaceShipPos.x, m_SpaceShipPos.y, 61,55, -1.60);
	pSpriteBatch->SetRenderColor(0xFFFFFFFF);

	pSpriteBatch->DrawSprite(m_pBackgroundLayer1, (float)m_WindowWidth / 2, (float)m_WindowHeight / 2, (float)m_WindowWidth, (float)m_WindowHeight);

	pSpriteBatch->DrawSprite(m_pGunSprite[m_Frame], (float)m_WindowWidth / 2, (float)m_WindowHeight / 2, (float)m_WindowWidth, (float)m_WindowHeight);

	pSpriteBatch->DrawSprite(m_pDogeTexture, m_DogePos.x, m_DogePos.y);
}

void MenuState::Exit()
{
}