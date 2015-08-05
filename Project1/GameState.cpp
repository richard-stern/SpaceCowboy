#include "GameState.h"
#include "SpriteBatch.h"
#include "StateMachine.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "GUI.h"
#include "Engine.h"
#include "Font.h"

GameState::GameState()
{
	GUI::CreateSingleton();
	m_v2PlayerOrigin.x = 400;
	m_v2PlayerOrigin.y = 500;

	// Create the font for use with draw string
	g_font1 = new Font("./Fonts/hobo_22px.fnt");
	g_fontTimer = new Font("./Fonts/OCR_A_Std_22px.fnt");

	paused_State = false;
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
	if (!paused_State)
	{
		m_pLevel->Update(fDeltaTime);

		m_pPlayer->Update(fDeltaTime);

		//Player Death
		if (m_pPlayer->GetHealth() == 0) {
			pStateMachine->ChangeState(ESTATE_GAMEOVER);
		}

		//Menu return
		if (Input::GetSingleton()->WasKeyPressed(GLFW_KEY_F1)) {
			pStateMachine->ChangeState(ESTATE_MENU);
		}

		//Pause State
		if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_ESCAPE) || Input::GetSingleton()->IsKeyDown(GLFW_KEY_P)) {
			paused_State = true;
		}
	}
	else
	{
		//Game
		if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_SPACE)) {
			paused_State = false;
			pStateMachine->ChangeState(ESTATE_GAME);
		}
		//Menu return
		if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_F1)) {
			pStateMachine->ChangeState(ESTATE_MENU);
			//paused_State = false;
		}
	}
}

void GameState::Draw(SpriteBatch* pSpriteBatch)
{
	if (!paused_State) {
		Vector2 playerPos = m_pPlayer->GetPosition();

		m_pLevel->Draw(pSpriteBatch);

		m_pPlayer->Draw(pSpriteBatch);

		//pSpriteBatch->SetCameraPos(playerPos.x, playerPos.y);
		
		//GUI Draw and parameters

		//param store hp
		float myVar = (float)m_pPlayer->GetPlayerHealthScaled();

		//param store shield
		float myVar2 = (float)m_pPlayer->GetPlayerShieldScaled();

		//Draws GUI
		GUI::GetSingleton()->Draw(pSpriteBatch, myVar, myVar2);
	}
	else {
		this->PauseDraw(pSpriteBatch);
	}
}


void GameState::PauseDraw(SpriteBatch* pSpriteBatch)
{
	pSpriteBatch->SetRenderColor(255, 5, 158, 255);
	// clear the back buffer
	Engine::GetSingleton()->GetApplication()->ClearScreen();

	// Window Width and Height
	unsigned int windowWidth = Engine::GetSingleton()->GetApplication()->GetWindowWidth();
	unsigned int windowHeight = Engine::GetSingleton()->GetApplication()->GetWindowHeight();
	// floats CamX and CamY
	float CamX;
	float CamY;
	Engine::GetSingleton()->GetSpriteBatch()->GetCameraPos(&CamX, &CamY);

	pSpriteBatch->DrawString(g_font1, "Paused State \t\t\t - Press Space to Resume", CamX + 50.0f, CamY + 10.0f);
	pSpriteBatch->DrawString(g_font1, "Main Menu = F1", CamX + 50, CamY + 40);
	//Player 1																						//GetWindowHeight()
	pSpriteBatch->DrawString(g_fontTimer, "Player 1 Controls", CamX + (float)(windowWidth / 3.0f), CamY + (float)(windowHeight / 2.0f) - 370.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Move Ship North              = W", CamX + (float)(windowWidth / 2.0f), CamY + (float)(windowHeight / 2.0f) - 340.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Move Ship South              = S", CamX + (float)(windowWidth / 2.0f), CamY + (float)(windowHeight / 2.0f) - 310.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Ship Counterclockwise = A", CamX + (float)(windowWidth / 2.0f), CamY + (float)(windowHeight / 2.0f) - 280.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Ship Clockwise        = D", CamX + (float)(windowWidth / 2.0f), CamY + (float)(windowHeight / 2.0f) - 250.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Reload                       = R", CamX + (float)(windowWidth / 2.0f), CamY + (float)(windowHeight / 2.0f) - 220.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Fire                         = Spacebar", CamX + (float)(windowWidth / 2.0f), CamY + (float)(windowHeight / 2.0f) - 190.0f);

	//:::::::::TODO::::::::
	//Anti Velocity
	/*	pSpriteBatch->DrawString(g_fontTimer, "Rotate Tank Left    = Z", CamX + (float)(windowWidth / 2.0f), CamY + (float)(windowHeight / 2.0f) - 160.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Tank Right   = C", CamX + (float)(windowWidth / 2.0f), CamY + (float)(windowHeight / 2.0f) - 130.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Cannon Left  = Q", CamX + (float)(windowWidth / 2.0f), CamY + (float)(windowHeight / 2.0f) - 100.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Cannon Right = E", CamX + (float)(windowWidth / 2.0f), CamY + (float)(windowHeight / 2.0f) - 70.0f); //*/
}

void GameState::Exit()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pLevel;
	m_pLevel = nullptr;

	Engine::GetSingleton()->GetSpriteBatch()->SetCameraPos(0, 0);
}