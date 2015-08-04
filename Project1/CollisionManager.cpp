#include "CollisionManager.h"
#include "GameObject.h"

CollisionManager * CollisionManager::m_pSingleton = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::AddObject(GameObject* pObject)
{
	allObjects.push_back(pObject);
}

void CollisionManager::RemoveObject(GameObject* pObject)
{
	for (unsigned int i = 0; i < allObjects.size(); i++)
	if (allObjects[i] == pObject)
	{
		allObjects.erase(allObjects.begin() + i);
	}
}

bool CollisionManager::IsColliding(GameObject* pObject, GameObject** pOther)
{
	ECollisionType typeCheck1;
	ECollisionType typeCheck2;
	GameObject* other;
	for (unsigned int i = 0; i < allObjects.size(); i++)
	{
		if (allObjects[i] == pObject)
		{
			continue;
		}
		other = allObjects[i];
	
		if (pObject->GetCollisionLayer() != ECOLLISIONLAYER_ALL)
		{
			//*pOther = pObject;
			if (pObject->GetCollisionLayer() == other->GetCollisionLayer())
			{
				continue;
			}
		}

		typeCheck1 = pObject->GetCollisionType();
		typeCheck2 = other->GetCollisionType();

		if (typeCheck1 == ECOLLISIONTYPE_AABB && typeCheck2 == ECOLLISIONTYPE_AABB)
		{
			if (OverlapTest(pObject->GetAABB(), other->GetAABB()))
			{
				if(!*pOther)
					*pOther = other;
				return true;
			}
		}

		if (typeCheck1 == ECOLLISIONTYPE_AABB && typeCheck2 == ECOLLISIONTYPE_CIRCLE_MIN)
		{
			if (OverlapTest(pObject->GetAABB(), other->GetCircle()))
			{
				if (!*pOther)
					*pOther = other;
				return true;
			}
		}
		if (typeCheck1 == ECOLLISIONTYPE_CIRCLE_MIN && typeCheck2 == ECOLLISIONTYPE_AABB)
		{
			if (OverlapTest( other->GetAABB(), pObject->GetCircle()))
			{
				if (!*pOther)
					*pOther = other;
				return true;
			}
		}
		if (typeCheck1 == ECOLLISIONTYPE_CIRCLE_MIN && typeCheck2 == ECOLLISIONTYPE_CIRCLE_MIN)
		{
			if (OverlapTest(pObject->GetCircle(), other->GetCircle()))
			{
				if (!*pOther)
					*pOther = other;
				return true;
			}
		}

	}
	return false;
}

bool CollisionManager::OverlapTest(const Rect& obj1, const Rect& obj2)
{
	if (obj1.min.x <= obj2.max.x && obj1.min.y <= obj2.max.y && obj2.max.x >= obj1.min.x && obj2.max.y >= obj1.min.y)
	{
		return true;
	}
	return false;
}

bool CollisionManager::OverlapTest(const Circle& obj1, const Circle& obj2)
{
	Vector2 points = (obj1.centre - obj2.centre);
	float dist = points.LengthSqr();
	if (dist <= (obj1.radius + obj2.radius)*(obj1.radius + obj2.radius))
	{
		return true;
	}
	return false;
}

bool CollisionManager::OverlapTest(const Rect& obj1, const Circle& obj2)
{
	Vector2 pc = obj2.centre.Clamp(obj1.min, obj1.max);
	Vector2 length(obj2.centre - pc);
	if (length.LengthSqr() <= obj2.radius*obj2.radius)
	{
		return true;
	}

	return false;
}

bool CollisionManager::OverlapTest(const Rect& obj1, const Vector2& obj2)
{
	if (obj1.min.x <= obj2.x && obj1.max.x >= obj2.x && obj1.min.y <= obj2.y && obj1.max.y >= obj2.y)
	{
		return true;
	}
	return false;
}

bool CollisionManager::OverlapTest(const Circle& obj1, const Vector2& obj2)
{

	if (obj2.LengthSqr() <= obj1.radius*obj1.radius)
	{
		return true;
	}

	return false;
}