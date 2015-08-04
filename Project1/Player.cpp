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
	m_pBulletManager = new BulletManager();

	//---------------------------- DEBUG -----------------------------------
	//m_pPlayerTexture = new Texture("./Images/player.png");
	//----------------------------------------------------------------------

	m_pPlayerTexture = TextureManager::GetSingleton()->LoadTexture(szTexturePath);

	SetPosition(v2Pos);
	m_Size = Vector2(66, 51);

	m_Rotation = 0;
	m_RotationVel = 0;
	m_RotationAcc = 0;

	m_Score = 0;
	m_nMaxHealth = 100;
	m_Health = m_nMaxHealth;
	m_ShieldMax = 100;
	m_Shield = m_ShieldMax;

	m_CamPosition = Vector2(0, 0);
	m_CamVelocity = Vector2(0, 0);
	m_CamAcceleration = Vector2(0, 0);

	m_CamOffSet = Vector2(0, 0);
	m_WindowWidth = 0;
	m_WindowHeight = 0;

	m_pCollider = nullptr;
}

Player::~Player()
{
}

void Player::Update(float fDeltaTime)
{
	if (m_WindowWidth == 0)
	{
		m_WindowWidth = Engine::GetSingleton()->GetApplication()->GetWindowWidth();
		m_WindowHeight = Engine::GetSingleton()->GetApplication()->GetWindowHeight();
	}

	GUI::GetSingleton()->SetHealth((float)GetPlayerHealthScaled());
	
	m_pCollider = nullptr;
	if (CollisionManager::GetSingleton()->IsColliding(this, &m_pCollider))
	{
		SetVelocity(m_pCollider->GetVelocity());
		if(m_Shield >= 0)
			m_Shield -= 20 + rand() % 20;
		else
			m_Health -= 20 + rand() % 20;
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
		m_RotationAcc -= 0.001f;
	}
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_D))
	{
		m_RotationAcc += 0.001f;
	}
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_LEFT_SHIFT))
	{
		if (GetVelocity().x > 0 || GetVelocity().x < 0 || GetVelocity().y > 0 || GetVelocity().y < 0)
		m_Acceleration.x = -GetVelocity().x / 100;
		m_Acceleration.y = -GetVelocity().y / 100;
	}
	if (Input::GetSingleton()->IsKeyDown(GLFW_KEY_SPACE))
	{
		m_pBulletManager->ShootBullet(GetPosition(), GetFacing());
	}

	//AUTO ANTI-Rotate
	if (Input::GetSingleton()->IsKeyUp(GLFW_KEY_A) && Input::GetSingleton()->IsKeyUp(GLFW_KEY_D))
	{
		if (m_RotationVel < 0)
		{
			m_RotationAcc += 0.001f;
		}
		else
		{
			m_RotationAcc -= 0.001f;
		}
	}

	//CAMERA
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
		m_CamOffSet.x -= 0.1f;
	else
		m_CamOffSet.x += 0.1f;

	if (m_CamOffSet.y > 0)
		m_CamOffSet.y -= 0.1f;
	else
		m_CamOffSet.y += 0.1f;
	
	Engine::GetSingleton()->GetSpriteBatch()->SetCameraPos(GetPosition().x - m_WindowWidth / 2 + m_CamOffSet.x, GetPosition().y - m_WindowHeight / 2 + m_CamOffSet.y);


	//ADD TO VEL AND POS
	m_RotationVel += m_RotationAcc *fDeltaTime;
	float MaxRotationSpeed = 0.0002f;
	if (m_RotationVel > MaxRotationSpeed)
		m_RotationVel = MaxRotationSpeed;
	else if (m_RotationVel < -MaxRotationSpeed)
		m_RotationVel = -MaxRotationSpeed;
	m_Rotation += m_RotationVel;

	m_Acceleration *= 100;
	SetVelocity(GetVelocity() + m_Acceleration * fDeltaTime);
	SetPosition(GetPosition() + GetVelocity() * fDeltaTime);

}

void Player::Draw(SpriteBatch* pSpriteBatch)
{
	pSpriteBatch->DrawSprite(m_pPlayerTexture, 400, 400, m_Size.x * 10, m_Size.y * 10, 0);
	pSpriteBatch->DrawSprite(m_pPlayerTexture, GetPosition().x, GetPosition().y, m_Size.x, m_Size.y, m_Rotation);


	if (m_Shield >= 0)
	{
		pSpriteBatch->SetRenderColor(0x0000FF00 + (int)(m_Shield * 2));
		pSpriteBatch->DrawSprite(m_pPlayerTexture, GetPosition().x, GetPosition().y, m_Size.x + 10, m_Size.y + 10, m_Rotation);
		pSpriteBatch->SetRenderColor(0xFFFFFFFF);
	}

}

int Player::GetPlayerHealth()
{
	return (int)m_Health;
}

float Player::GetPlayerHealthMax()
{
	return m_nMaxHealth;
}

int Player::GetPlayerHealthScaled()
{
	float HealthFraction = m_Health / 100;
	HealthFraction *= 233;

	return (int)HealthFraction;
}

float Player::GetPlayerShield()
{
	return m_Shield;
}

float Player::GetPlayerShieldMax()
{
	return m_ShieldMax;
}

void Player::SetPlayerShield(float newShield)
{
	m_Shield = newShield;
}
