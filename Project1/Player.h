#pragma once

#include "GameObject.h"
#include "Vector2.h"

class BulletManager;
class PlayerUI;

class Texture;

class Player : public GameObject
{
public:
	Player(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision);
	virtual ~Player();

	void Update(float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch);

	int GetPlayerHealth();
	int GetPlayerHealthMax();
	float GetPlayerHealthScaled();

	int GetPlayerShield();
	int GetPlayerShieldMax();
	float GetPlayerShieldScaled();
	void SetPlayerShield(float newShield);

private:

	Texture* m_pPlayerTexture;
	Texture* m_pShieldTexture;

	BulletManager* m_pBulletManager;

	int m_WindowWidth;
	int m_WindowHeight;

	//Spatial Variables
	Vector2 m_Acceleration;
	Vector2 m_Size;
	float m_Rotation;
	float m_RotationVel;
	float m_RotationAcc;

	//Camera
	Vector2 m_CamPosition;
	Vector2 m_CamVelocity;
	Vector2 m_CamAcceleration;

	//UI
	int m_Score;
	int m_Shield;
	int m_ShieldMax;

	//CAMERA
	Vector2 m_CamOffSet;

	//Collison
	GameObject* m_pCollider;


};

