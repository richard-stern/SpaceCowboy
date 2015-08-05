#pragma once
#include "BaseState.h"

class PauseState //: public BaseState
{
public:
	PauseState();
	virtual ~PauseState();

	void Enter();
	void Update(StateMachine* pStateMachine, float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch);
	void Exit();


};