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
		fileName += "_g.png";
		//std::cout << fileName << std::endl;
		char* tempFileName = (char*)fileName.c_str();
		m_pGunSprite[i] = TextureManager::GetSingleton()->LoadTexture(tempFileName);
	}
	m_BtnPos[0] = Vector2(240, 500);

	m_SpaceShipAcc = Vector2(0,0);
	m_SpaceShipVel = Vector2(0, 0);
	m_SpaceShipPos = Vector2(1500, 500);

	m_GunPos = Vector2(0, 0);

	m_DogePos = Vector2(2200, 900);

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
}

void MenuState::Update(StateMachine* pStateMachine, float fDeltaTime)
{
	if (m_WindowWidth == 0)
	{
		m_WindowWidth = Engine::GetSingleton()->GetApplication()->GetWindowWidth();
		m_WindowHeight = Engine::GetSingleton()->GetApplication()->GetWindowHeight();
	}
	if (m_Frame >= 29)
	{
		m_Playing = false;
		m_Timer = m_TimerMax;
		m_Frame = 0;
		m_startGame = true;
		m_SpaceShipVel = Vector2(0,-0.04f);
	}
	if (m_Playing == true)
	{
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

	int MouseX = Input::GetSingleton()->GetMouseX();
	int MouseY = Input::GetSingleton()->GetMouseY();
	if (Input::GetSingleton()->IsMouseButtonDown(0))
	{
		if (MouseX > m_BtnPos[0].x && MouseX < m_BtnPos[0].x + 100 &&
			MouseY > m_BtnPos[0].y && MouseY < m_BtnPos[0].y + 50)
		{
			m_Playing = true;
		}
	}

	m_SpaceShipPos += m_SpaceShipVel;
	if (m_startGame == true)
	{
		if (m_DogePos.x > 1900)
			m_DogePos.x -= 0.06f;

		if (m_SpaceShipPos.y < -100)
			pStateMachine->ChangeState(ESTATE_GAME);
	}
}

void MenuState::Draw(SpriteBatch* pSpriteBatch)
{
	pSpriteBatch->DrawSprite(m_pBackgroundLayer2, (float)m_WindowWidth / 2, (float)m_WindowHeight / 2);
	//SpaceShip HERE
	pSpriteBatch->SetRenderColor(0x0000FFFF);
	pSpriteBatch->DrawSprite(m_pSpaceShipTexture, m_SpaceShipPos.x, m_SpaceShipPos.y, 61,55, -1.60);
	pSpriteBatch->SetRenderColor(0xFFFFFFFF);

	pSpriteBatch->DrawSprite(m_pBackgroundLayer1, (float)m_WindowWidth / 2, (float)m_WindowHeight / 2);

	pSpriteBatch->DrawSprite(m_pGunSprite[m_Frame], (float)m_WindowWidth / 2, (float)m_WindowHeight / 2, (float)m_WindowWidth, (float)m_WindowHeight);

	pSpriteBatch->DrawSprite(m_pDogeTexture, m_DogePos.x, m_DogePos.y);
	
}

void MenuState::Exit()
{
}