#pragma once
//-------------------------------------------------------------------
// Review
#include "glfw3.h"
#include "Input.h"
//-------------------------------------------------------------------

class StateMachine;
class SpriteBatch;

class BaseState
{
public:
	BaseState();
	virtual ~BaseState();

	virtual void Enter() = 0;
	virtual void Update(StateMachine* pStateMachine, float fDeltaTime) = 0;
	virtual void Draw(SpriteBatch* pSpriteBatch) = 0;
	virtual void Exit() = 0;
};

