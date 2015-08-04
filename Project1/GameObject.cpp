#include "Vector2.h"
#include "Rect.h"
#include "GameObject.h"

#include "TextureManager.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "CollisionManager.h"
#include "Engine.h"
#include "Application.h"

#include <math.h>

GameObject::GameObject(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision)
{
	m_bActive = false;
	m_bIsVisible = false;
	m_pTexture = TextureManager::GetSingleton()->LoadTexture(szTexturePath);
	m_v2Pos = v2Pos;
	m_eCollisionType = eCollision;
	m_v2Velocity = Vector2(0.0f, 0.0f);
	m_fSpeed = 0.0f;
	m_nHealth = 100.0f;
	m_nMaxHealth = 100.0f;
}

GameObject::~GameObject()
{
	m_bActive = false;
	m_bIsVisible = false;
}

void GameObject::Update(float fDeltaTime)
{
	//Remains empty, as all inhereting objects will redefine their own Update.
}

void GameObject::Draw(SpriteBatch* pSpriteBatch)
{
	CollisionManager* pColMan = CollisionManager::GetSingleton();
	float rotation = atan2(m_v2Facing.y, m_v2Facing.x);

	Rect Rectangle;

	pSpriteBatch->GetViewRect(&Rectangle.min.x, &Rectangle.min.y, &Rectangle.max.x, &Rectangle.max.y);

	m_bIsVisible = pColMan->OverlapTest(Rectangle, m_rAABB);

	if (m_bActive && m_bIsVisible)
	{
		pSpriteBatch->DrawSprite(m_pTexture, m_v2Pos.x, m_v2Pos.y, 0, 0, rotation);
	}
}

void GameObject::SetVelocity(Vector2 v2Vel)
{
	m_v2Velocity = v2Vel;
}

void GameObject::SetPosition(Vector2 v2Pos)
{
	m_v2Pos = v2Pos;
}

void GameObject::SetPosition(float x, float y)
{
	m_v2Pos.x = x;
	m_v2Pos.y = y;
}

Vector2& GameObject::GetPosition()
{
	return m_v2Pos;
}

Vector2& GameObject::GetVelocity()
{
	return m_v2Velocity;
}

void GameObject::SetHealth(int nHealth)
{
	m_nHealth = nHealth;
}

int GameObject::GetHealth()
{
	return m_nHealth;
}

int GameObject::GetMaxHealth()
{
	return m_nMaxHealth;
}

void GameObject::SetActive(bool bActive)
{
	m_bActive = bActive;
}

bool GameObject::GetActive()
{
	return m_bActive;
}

void GameObject::RecalculateAABB()
{
	Vector2 TexSize = Vector2((float)m_pTexture->GetWidth(), (float)m_pTexture->GetHeight()) / 2;

	m_rAABB.min = m_v2Pos - TexSize;
	m_rAABB.max = m_v2Pos + TexSize;

	m_Circle.centre = m_v2Pos;
	if (m_eCollisionType == ECOLLISIONTYPE_CIRCLE_MIN)
	{
		if (TexSize.x < TexSize.y)
		{
			m_Circle.radius = TexSize.x;
		}
		else
		{
			m_Circle.radius = TexSize.y;
		}
	}
	else if (m_eCollisionType == ECOLLISIONTYPE_CIRCLE_MAX)
	{
		if (TexSize.x > TexSize.y)
		{
			m_Circle.radius = TexSize.x;
		}
		else
		{
			m_Circle.radius = TexSize.y;
		}
	}
}

void GameObject::SetCollisionType(ECollisionType type)
{
	m_eCollisionType = type;
}

ECollisionType GameObject::GetCollisionType()
{
	return m_eCollisionType;
}

void GameObject::SetCollisionLayer(ECollisionLayer layer)
{
	m_eCollisionLayer = layer;
}

ECollisionLayer GameObject::GetCollisionLayer()
{
	return m_eCollisionLayer;
}

Rect& GameObject::GetAABB()
{
	return m_rAABB;
}

Circle& GameObject::GetCircle()
{
	return m_Circle;
}

Vector2& GameObject::GetFacing()
{
	return m_v2Facing;
}

void GameObject::SetFacing(Vector2& v2Facing)
{
	m_v2Facing = v2Facing;
}

bool GameObject::GetVisible()
{
	return m_bIsVisible;
}

void GameObject::SetVisible(bool visible)
{
	m_bIsVisible = visible;
}