////////////////////////////////////////////////////////
//	File Nmae:		StarSpawner
//	Aurthor:		David Azouz
//	Date Created:	03/08/2015
//	Brief:			A StarSpawner Class which spawns Stars within the game
////////////////////////////////////////////////////////

#ifndef STARSPAWNER_H
#define STARSPAWNER_H

//-------------------------------------------------------------------
// Predeclarations
//-------------------------------------------------------------------
class Star;
class SpriteBatch;
class Texture;

#define MAX_STARS 30
#define SPAWN_DELAY 0.1f //0.05f

class StarSpawner
{
public:
	//-------------------------------------------------------------------
	// Overloaded Construtor
	//-------------------------------------------------------------------
	//
	// Param:
	//		nScreenWidth: The Game ScreenWidth
	//-------------------------------------------------------------------
	StarSpawner(int nScreenWidth, int nScreenHeight);

	//-------------------------------------------------------------------
	// Destructor
	//-------------------------------------------------------------------
	~StarSpawner();

	//-------------------------------------------------------------------
	// Update Function
	//-------------------------------------------------------------------
	//
	// Param:
	//		fDeltaTime: DeltaTime/ time in seconds passed
	//-------------------------------------------------------------------
	void Update(float fDeltaTime);

	//-------------------------------------------------------------------
	// Draw
	//-------------------------------------------------------------------
	//
	// Param:
	//		pSpritebatch: a SpriteBatch.
	//-------------------------------------------------------------------
	void Draw(SpriteBatch* pSpriteBatch);

	//-------------------------------------------------------------------
	// UpdateCollision
	//-------------------------------------------------------------------
	void UpdateCollision();

private:
	Star* m_apStarList[MAX_STARS];
	char* m_pcStarTexture;

	char* m_cpStar1;
	char* m_cpStar2;
	char* m_cpStar3;
	int m_nStarCount;
	float m_fStarSpawnTimer;
	//Screen
	int m_nScreenWidth;
	int m_nScreenHeight;
};

#endif