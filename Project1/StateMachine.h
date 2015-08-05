#pragma once

class BaseState;
class SpriteBatch;

enum EState
{
	ESTATE_MENU,
	ESTATE_GAME,
//	ESTATE_PAUSED,
	ESTATE_GAMEOVER,

	ESTATE_COUNT
};

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void Update(float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch);

	void ChangeState(EState eState);

private:
	EState m_eCurrentState;
	BaseState* StatesArray[ESTATE_COUNT];
};

