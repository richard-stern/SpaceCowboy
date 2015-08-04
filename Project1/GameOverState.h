#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H
#include "BaseState.h"
#include "Font.h"
#include "Texture.h"

class GUI;

class GameOverState : public BaseState
{
public:
	GameOverState();
	virtual ~GameOverState();

	void Enter();
	void Update(StateMachine* pStateMachine, float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch);
	void Exit();

private:

	Font* m_font1;
	Font* m_font2;

	Texture* m_background;
};

#endif