#pragma once

#include "GameObject.h"
#include <list>

using namespace std;

class Rock;
class Star;
class SpriteBatch;

//This class needs to create the level and all the obstacles, environment, enemies, etc.
//It doesn't create the player.
//It could create any kind of levle using whatever method you want: e.g. procedural, loaidng from a file, etc.
class Level
{
public:
	Level();
	~Level();

	void Update(float fDeltaTime);
	void Draw(SpriteBatch* pSpriteBatch);

private:
	GameObject* rockStorage[20];
	GameObject* starStorage[20];
	Vector2 m_v2EachPos;
};