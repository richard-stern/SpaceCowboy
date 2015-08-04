#pragma once
#include "BaseState.h"

class Font;

class PauseState : public BaseState
{
public:
	PauseState();
	virtual ~PauseState();

	void Enter();
	void Update(StateMachine* pStateMachine, float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch);
	void Exit();

private:
	Font *g_font1;
	Font *g_fontTimer;
};