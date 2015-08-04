#pragma once
#include "Application.h"
class SpriteBatch;

class GUI
{
public:
	static GUI *GetSingleton()		{ return m_pSingleton; }
	static void CreateSingleton()	{ m_pSingleton = new GUI(); }
	static void DestroySingleton()	{ delete m_pSingleton; }

	void Draw(SpriteBatch* pSpriteBatch, float health);

	void DisplayScore();
	void AddScore(int amount);
	int GetScore();
	void SetHealth(float health);

	GUI();
private:

	~GUI();

	float minX;
	float minY;
	float maxX;
	float maxY;

	int m_pScore;
	int m_pHealth;
	static GUI * m_pSingleton;
	Texture *m_pHpImage;
	Texture *m_pbar;
	Texture *m_pSbar;
	Texture *m_pShieldImage;
	Font *m_font;
};

