#pragma once

#include <vector>

struct Rect;
struct Circle;
struct Vector2;
class GameObject;

//What type of collision to use.
//ECOLLISIONTYPE_NONE: No collision.
//ECOLLISIONTYPE_AABB: Use an Axis-Aligned Bounding Box.
//ECOLLISIONTYPE_CIRCLE_MIN: Use a circle, with a radius equal to the lower of the object's width and height.
//ECOLLISIONTYPE_CIRCLE_MAX: Use a circle, with a radius equal to the greater of the object's width and height.
enum ECollisionType
{
	ECOLLISIONTYPE_NONE,
	ECOLLISIONTYPE_AABB,
	ECOLLISIONTYPE_CIRCLE_MIN,
	ECOLLISIONTYPE_CIRCLE_MAX,
};

//Collision layers are used to determine what objects collide.
//Objects with the same layer don't collide.
//E.g. Setting the player and their bullets to be the same will prevent the player hitting themselves.
//Object set to the ECOLLISIONLAYER_ALL layer will collide with all objects, even other objects on the same layer.
enum ECollisionLayer
{
	ECOLLISIONLAYER_ALL,
	ECOLLISIONLAYER_PLAYER,
	ECOLLISIONLAYER_ROCK
};

class CollisionManager
{
public:
	static CollisionManager *GetSingleton() { return m_pSingleton; }
	static void CreateSingleton()			{ m_pSingleton = new CollisionManager(); }
	static void DestroySingleton()			{ delete m_pSingleton; }

	//Add/remove a GameObject to the collision manager so it can track it's collisions
	void AddObject(GameObject* pObject);
	void RemoveObject(GameObject* pObject);

	//Check if an object is colliding
	//pObject: The object to check collision on.
	//pOther: Optional. If a pointer to a GameObject is passed in here, it will be filled with the other object in the collision.
	bool IsColliding(GameObject* pObject, GameObject** pOther = nullptr);

	//Functions that can be used to test if two shapes are overlapping
	bool OverlapTest(const Rect& obj1, const Rect& obj2);
	bool OverlapTest(const Circle& obj1, const Circle& obj2);
	bool OverlapTest(const Rect& obj1, const Circle& obj2);
	bool OverlapTest(const Rect& obj1, const Vector2& obj2);
	bool OverlapTest(const Circle& obj1, const Vector2& obj2);

private:
	CollisionManager();
	~CollisionManager();
	static CollisionManager * m_pSingleton;
	std::vector <GameObject*>  allObjects;
};

