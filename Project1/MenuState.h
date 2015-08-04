#pragma once
#include "BaseState.h"

class MenuState : public BaseState
{
public:
	MenuState();
	virtual ~MenuState();

	void Enter();
	void Update(StateMachine* pStateMachine, float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch);
	void Exit();
};

