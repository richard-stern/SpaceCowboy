#include "MenuState.h"
#include "StateMachine.h"
#include "SpriteBatch.h"
#include "glfw3.h"
#include "Input.h"

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
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
}

void MenuState::Exit()
{
}