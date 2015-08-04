#pragma once
#include "BaseState.h"

//Delete when done
class Font;

class MenuState : public BaseState
{
public:
	MenuState();
	virtual ~MenuState();

	void Enter();
	void Update(StateMachine* pStateMachine, float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch);
	void Exit();

private:
	Font *g_font1;
};

