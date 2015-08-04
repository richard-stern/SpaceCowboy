#pragma once
#include "BaseState.h"
#include "GUI.h"
#include "Player.h"
#include "Level.h"
#include "Texture.h"

class GameState : public BaseState
{
public:
	GameState();
	virtual ~GameState();

	void Enter();
	void Update(StateMachine* pStateMachine, float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch);
	void Exit();

private:
	Level* m_pLevel;
	Player* m_pPlayer;
	
	Vector2 m_v2PlayerOrigin;
};

