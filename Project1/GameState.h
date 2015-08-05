#pragma once
#include "BaseState.h"
#include "GUI.h"
#include "Player.h"
#include "Level.h"
#include "Texture.h"

class Font;

class GameState : public BaseState
{
public:
	GameState();
	virtual ~GameState();

	void Enter();
	void Update(StateMachine* pStateMachine, float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch);
	void Exit();

	void PauseDraw(SpriteBatch* pSpriteBatch);

	bool paused_State;

private:
	Level* m_pLevel;
	Player* m_pPlayer;
	
	Vector2 m_v2PlayerOrigin;
	//Font
	Font *g_font1;
	Font *g_fontTimer;
};

