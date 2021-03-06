#include "Player.h"
#include "SpriteBatch.h"

#include "TextureManager.h"
#include "Texture.h"

#include "Input.h"
#include "glfw3.h"

#include "BulletManager.h"
#include <math.h>

#include "Application.h"
#include "Engine.h"
#include "CollisionManager.h"
#include "GUI.h"

Player::Player(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision) : GameObject( szTexturePath, v2Pos, eCollision )
{
	//Make Bullet Manager
	m_pBulletManager = new BulletManager();

	//Set Pos and Size
	SetPosition(v2Pos);
	m_Size = Vector2(66, 51);

	//Set Roation
	m_Rotation = 0;
	m_RotationVel = 0;
	m_RotationAcc = 0;

	//Set Player states
	m_Score = 0;
	m_nMaxHealth = 100;
	m_nHealth = m_nMaxHealth;
	m_ShieldMax = 100;
	m_Shield = m_ShieldMax;
	m_ShieldTimer = 1.0f;

	//Set Camera
	m_CamPosition = Vector2(0, 0);
	m_CamVelocity = Vector2(0, 0);
	m_CamAcceleration = Vector2(0, 0);
	m_CamOffSet = Vector2(0, 0);

	m_WindowWidth = 0;
	m_WindowHeight = 0;

	m_pCollider = nullptr;
	SetCollisionLayer(ECOLLISIONLAYER_PLAYER);
	SetActive(true);
}

Player::~Player()
{
	delete m_pBulletManager;
}

void Player::Update(float fDeltaTime)
{
	//Set WINDOW Variables on ENTER
	if (m_WindowWidth == 0)
	{
		m_WindowWidth = Engine::GetSingleton()->GetApplication()->GetWindowWidth();
		m_WindowHeight = Engine::GetSingleton()->GetApplication()->GetWindowHeight();
	}
	//Update GUI Player health
	GUI::GetSingleton()->SetHealth((float)GetPlayerHealthScaled());

	//Update Collision
	m_pCollider = nullptr;
	if (CollisionManager::GetSingleton()->IsColliding(this, &m_pCollider))
	{
		SetVelocity(m_pCollider->GetVelocity());
		//If Shields down Damage health, else Damage shield
		if(m_Shield >= 0)
			m_Shield -= 20 + rand() % 20;
		else
			m_nHealth -= 20 + rand() % 20;
	}

	//ReSet ACC
	m_Acceleration = Vector2(0,0);
	m_RotationAcc = 0;
	SetFacing(Vector2(cosf(m_Rotation), sinf(m_Rotation)));

	//INPUT
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_W))
	{
		m_Acceleration.x = GetFacing().x;
		m_Acceleration.y = GetFacing().y;
	}
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_S))
	{
		m_Acceleration.x = -GetFacing().x;
		m_Acceleration.y = -GetFacing().y;
	}
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_A))
	{
		m_RotationAcc -= 5.0f * fDeltaTime;
	}
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_D))
	{
		m_RotationAcc += 5.0f * fDeltaTime;
	}
	//Mad Brakes
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_LEFT_SHIFT))
	{
		if (GetVelocity().x > 0 || GetVelocity().x < 0 || GetVelocity().y > 0 || GetVelocity().y < 0)
		m_Acceleration.x = -GetVelocity().x / 100;
		m_Acceleration.y = -GetVelocity().y / 100;
	}
	//SHOOT
	if (Input::GetSingleton()->WasKeyPressed(GLFW_KEY_SPACE))
	{
		m_pBulletManager->ShootBullet(GetPosition(), GetFacing());
	}

	//AUTO ANTI-Rotate
	if (Input::GetSingleton()->IsKeyUp(GLFW_KEY_A) && Input::GetSingleton()->IsKeyUp(GLFW_KEY_D))
	{
		if (m_RotationVel < 0)
		{
			m_RotationAcc += 2.0f * fDeltaTime;
		}
		else
		{
			m_RotationAcc -= 2.0f * fDeltaTime;
		}
	}

	//Set CAMERA Offset
	m_CamOffSet -= m_Acceleration * fDeltaTime * 50;	
	Vector2 offSetCap = Vector2(200,150);
	if (m_CamOffSet.x > offSetCap.x)
		m_CamOffSet.x = offSetCap.x;
	else if (m_CamOffSet.x < -offSetCap.x)
		m_CamOffSet.x = -offSetCap.x;

	if (m_CamOffSet.y >  offSetCap.y)
		m_CamOffSet.y = offSetCap.y;
	else if (m_CamOffSet.y < -offSetCap.y)
		m_CamOffSet.y = -offSetCap.y;

	if (m_CamOffSet.x > 0)
		m_CamOffSet.x -= 1.0f * fDeltaTime;
	else
		m_CamOffSet.x += 1.0f * fDeltaTime;

	if (m_CamOffSet.y > 0)
		m_CamOffSet.y -= 1.0f * fDeltaTime;
	else
		m_CamOffSet.y += 1.0f * fDeltaTime;
	//Update Camera
	Engine::GetSingleton()->GetSpriteBatch()->SetCameraPos(GetPosition().x + m_CamOffSet.x, GetPosition().y + m_CamOffSet.y);


	//ADD TO VEL AND POS
	m_RotationVel += m_RotationAcc *fDeltaTime;
	float MaxRotationSpeed = 2.0f * fDeltaTime;
	if (m_RotationVel > MaxRotationSpeed)
		m_RotationVel = MaxRotationSpeed;
	else if (m_RotationVel < -MaxRotationSpeed)
		m_RotationVel = -MaxRotationSpeed;
	m_Rotation += m_RotationVel;

	m_Acceleration *= 100;
	SetVelocity(GetVelocity() + m_Acceleration * fDeltaTime);
	SetPosition(GetPosition() + GetVelocity() * fDeltaTime);	
	RecalculateAABB();
	m_pBulletManager->Update(fDeltaTime);
}

void Player::Draw(SpriteBatch* pSpriteBatch)
{
	m_pBulletManager->Draw(pSpriteBatch);
	//Draw Player
	GameObject::Draw(pSpriteBatch);
	//Draw Shield
	if (m_Shield >= 0)
	{
		pSpriteBatch->SetRenderColor(0x0000FF00 + (int)(m_Shield * 2));
		GameObject::Draw(pSpriteBatch);
		pSpriteBatch->SetRenderColor(0xFFFFFFFF);
	}
}

int Player::GetPlayerHealth()
{
	return m_nHealth;
}

int Player::GetPlayerHealthMax()
{
	return m_nMaxHealth;
}

float Player::GetPlayerHealthScaled()
{
	float HealthFraction = (float)m_nHealth / 100;
	HealthFraction *= 233;

	return HealthFraction;
}

int Player::GetPlayerShield()
{
	return m_Shield;
}

int Player::GetPlayerShieldMax()
{
	return m_ShieldMax;
}

float Player::GetPlayerShieldScaled()
{
	float ShieldFraction = (float)m_Shield / 100;
	ShieldFraction *= 233;

	return ShieldFraction;
}

void Player::SetPlayerShield(float newShield)
{
	m_Shield = (int)newShield;
}
