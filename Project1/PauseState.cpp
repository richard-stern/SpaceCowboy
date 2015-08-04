#include "PauseState.h"
#include "SpriteBatch.h"
#include "StateMachine.h"
#include "Font.h"

PauseState::PauseState()
{
	// Create the font for use with draw string
	g_font1 = new Font("./Fonts/hobo_22px.fnt");
	g_fontTimer = new Font("./Fonts/OCR_A_Std_22px.fnt");
}


PauseState::~PauseState()
{
	delete g_fontTimer;
	delete g_font1;
}

void PauseState::Enter()
{
}

void PauseState::Update(StateMachine* pStateMachine, float fDeltaTime)
{
	//Game
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_SPACE))
	{
		pStateMachine->ChangeState(ESTATE_GAME);
	}
	//Menu return
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_F1))
	{
		pStateMachine->ChangeState(ESTATE_MENU);
	}
}

void PauseState::Draw(SpriteBatch* pSpriteBatch)
{
	pSpriteBatch->SetRenderColor(255, 5, 158, 255);

	// clear the back buffer
	//ClearScreen();

	pSpriteBatch->DrawString(g_font1, "Paused State \t\t\tPress Space to Resume", 10, 10);
	pSpriteBatch->DrawString(g_font1, "Main Menu = F1", 10, 40);
	//Player 1																						//GetWindowHeight()
	pSpriteBatch->DrawString(g_fontTimer, "Player 1 Controls",(float)(878.0f / 7.0f), (float)(1232.0f / 2.0f) - 370.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Move Up             = W", (float)(878.0f / 6.0f), (float)(1232.0f / 2.0f) - 340.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Move Down           = S", (float)(878.0f / 6.0f), (float)(1232.0f / 2.0f) - 310.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Ship Left    = A", (float)(878.0f / 6.0f), (float)(1232.0f / 2.0f) - 280.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Ship Right   = D", (float)(878.0f / 6.0f), (float)(1232.0f / 2.0f) - 250.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Reload              = R", (float)(878.0f / 6.0f), (float)(1232.0f / 2.0f) - 220.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Fire                = Spacebar", (float)(878.0f / 6.0f), (float)(1232.0f / 2.0f) - 190.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Tank Left    = Z", (float)(878.0f / 6.0f), (float)(1232.0f / 2.0f) - 160.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Tank Right   = C", (float)(878.0f / 6.0f), (float)(1232.0f / 2.0f) - 130.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Cannon Left  = Q", (float)(878.0f / 6.0f), (float)(1232.0f / 2.0f) - 100.0f);
	pSpriteBatch->DrawString(g_fontTimer, "Rotate Cannon Right = E", (float)(878.0f / 6.0f), (float)(1232.0f / 2.0f) - 70.0f);
}

void PauseState::Exit()
{
}