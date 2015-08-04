#include "MenuState.h"
#include "StateMachine.h"
#include "SpriteBatch.h"

//-------------------------------------------------------------------
// Delete
#include "Font.h"
//-------------------------------------------------------------------

MenuState::MenuState()
{
	//-------------------------------------------------------------------
	//Delete when finished
	// Create the font for use with draw string
	g_font1 = new Font("./Fonts/hobo_22px.fnt");
	//-------------------------------------------------------------------
}

MenuState::~MenuState()
{
	//-------------------------------------------------------------------
	//Delete afterwards
	delete g_font1;
	//-------------------------------------------------------------------
}

void MenuState::Enter()
{
}

void MenuState::Update(StateMachine* pStateMachine, float fDeltaTime)
{
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_SPACE))
	{
		pStateMachine->ChangeState(ESTATE_GAME);
	}
}

void MenuState::Draw(SpriteBatch* pSpriteBatch)
{
	//Differentiate between states - To be deleted in final release
	//-------------------------------------------------------------------
	// Draw the menu
	pSpriteBatch->DrawString(g_font1, "Menu State", 10, 10);

	//Fade colour
	pSpriteBatch->SetRenderColor(255, 255, 255, 255 * (unsigned char)61.0f);
	pSpriteBatch->DrawString(g_font1, "Press F1 to return to menu", 10, 40);
	pSpriteBatch->DrawString(g_font1, "Press Space to play Space Cowboy!", 10, 70);
	pSpriteBatch->DrawString(g_font1, "Press Esc or 'P' to view Pause game or view controls", 10, 100);
	//Reset Colour
	pSpriteBatch->SetRenderColor(255, 255, 255, 255);
	//-------------------------------------------------------------------
}

void MenuState::Exit()
{
}