#pragma once

#include "GameObject.h"
#include <list>


#define ROCK_COUNT 20
#define STAR_COUNT 220

using namespace std;

class Rock;
class Star;
class SpriteBatch;
class Texture;

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

	//Time for fade
	float m_fTimeFade;

private:
	GameObject* rockStorage[ROCK_COUNT];
	GameObject* starStorage[STAR_COUNT];
	Vector2 m_v2EachPos;
};