#pragma once

#include "Vector2.h"
#include "Rect.h"
#include "Circle.h"

class Texture;
class SpriteBatch;
enum ECollisionType;
enum ECollisionLayer;

class GameObject
{
public:
	GameObject(char* szTexturePath, Vector2 v2Pos, ECollisionType eCollision);
	virtual ~GameObject();

	virtual void Update(float fDeltaTime);
	virtual void Draw(SpriteBatch* pSpriteBatch);

	void SetVelocity(Vector2 v2Vel);
	void SetPosition(Vector2 v2Pos);
	void SetPosition(float x, float y);
	void RecalculateAABB();
	Vector2& GetPosition();
	Vector2& GetVelocity();

	void SetFacing(Vector2& v2Facing);
	Vector2& GetFacing();
	
	void SetHealth(int nHealth);
	int GetHealth();

	void SetActive(bool bActive);
	bool GetActive();

	void SetCollisionType(ECollisionType type);
	ECollisionType GetCollisionType();

	void SetCollisionLayer(ECollisionLayer layer);
	ECollisionLayer GetCollisionLayer();
	Rect& GetAABB();
	Circle& GetCircle();

	bool GetVisible();
	void SetVisible(bool visible);

protected:
	//Stores the object's current Velocity
	Vector2 m_v2Velocity;

	//Stores the object's current Position
	Vector2 m_v2Pos;
	
	//Unit Vector that stored the direction the object is facing.
	Vector2 m_v2Facing;

	//Float that stores the Speed of an object.
	float m_fSpeed;

	//Type of collision detect used.
	ECollisionType m_eCollisionType;

	//Used to indicate which other objects this one can collide with.
	ECollisionLayer m_eCollisionLayer;

	//The Axis Aligned bounding box of the object. Used for Collision.
	Rect m_rAABB;

	//A circle around the object. Used for circular collision.
	Circle m_Circle;

	//Current Health
	int m_nHealth;

	//Max Health
	int m_nMaxHealth;

	//Is the object alive/in existence. Set to false to stop updating, and to return to the pool, without needing to delete the object.
	bool m_bActive;

	//True if the object is currently on screen
	bool m_bIsVisible;

	//Stored texture of the object.
	Texture *m_pTexture;
};

