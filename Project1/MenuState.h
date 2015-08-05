#pragma once
#include "BaseState.h"
#include "Vector2.h"

class Texture;

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
	int m_WindowWidth;
	int m_WindowHeight;

	Texture* m_pSpaceShipTexture;
	Texture* m_pDogeTexture;
	Texture* m_pBackgroundLayer1;
	Texture* m_pBackgroundLayer2;
	Texture* m_pPlayBtnOverlay;
	Texture* m_pGunSprite[30];

	bool m_Playing;
	int m_Frame;
	float m_Timer;
	float m_TimerMax;
	bool m_startGame;
	bool m_btn1Hover;

	Vector2 m_BtnPos[3];

	Vector2 m_SpaceShipAcc;
	Vector2 m_SpaceShipVel;
	Vector2 m_SpaceShipPos;

	Vector2 m_GunPos;

	Vector2 m_DogePos;
};

