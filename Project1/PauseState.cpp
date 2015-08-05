#include "PauseState.h"
#include "SpriteBatch.h"
#include "StateMachine.h"

#include "Engine.h"
#include "Application.h"

PauseState::PauseState()
{
}


PauseState::~PauseState()
{
}

void PauseState::Enter()
{
}

void PauseState::Update(StateMachine* pStateMachine, float fDeltaTime)
{
	
}

void PauseState::Draw(SpriteBatch* pSpriteBatch)
{
	pSpriteBatch->SetRenderColor(255, 5, 158, 255);
/*	// clear the back buffer
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
	pSpriteBatch->DrawString(g_fontTimer, "Player 1 Controls",		 CamX + (float)(windowWidth / 3.0f), CamY + (float)(windowHeight / 2.0f) - 370.0f);
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

void PauseState::Exit()
{
}