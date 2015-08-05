#include "GUI.h"
#include "SpriteBatch.h"
#include "Player.h"
#include "TextureManager.h"
#include "Engine.h"
#include "Game.h"
#include "Font.h"
#include <string>

GUI* GUI::m_pSingleton = nullptr;

GUI::GUI()
{
	//construct the GUI parts
	m_pScore = 0;
	m_pHealth = 0;
	m_pShield = 0;

	//health image
	m_pHpImage = TextureManager::GetSingleton()->LoadTexture("hp bar neo.png");

	//health bar
	m_pbar = TextureManager::GetSingleton()->LoadTexture("hp bar green.png");

	//shield image 
	m_pShieldImage = TextureManager::GetSingleton()->LoadTexture("shield final.png");

	//shield bar
	m_pSbar = TextureManager::GetSingleton()->LoadTexture("shield bar.png");

	//font
	m_font = new Font("./Fonts/ocr_a_36px.fnt");
}

GUI::~GUI()
{
	delete m_font;
}

void GUI::Draw(SpriteBatch* pSpriteBatch, float health,float shield)
{
	Engine::GetSingleton()->GetSpriteBatch()->GetViewRect(&minX, &minY, &maxX, &maxY);

	//draw the health UI
	pSpriteBatch->DrawSprite(m_pHpImage, minX + 170.0f, minY + 30.0f, 293.0f, 14.0f);

	//Live hp updaterino + logic
	SetHealth(health);
	float myVar = (float)m_pHealth;
	pSpriteBatch->DrawSprite(m_pbar, minX + 192.0f, minY + 29.0f, myVar + 1.0f, 10.0f, 0, 0); //change 4th value to change bar length

	//draw the shield UI
	pSpriteBatch->DrawSprite(m_pShieldImage, minX + 170.0f, minY + 60.0f, 293.0f, 14.0f);

	//draw the Shield bar
	SetShield(shield);
	float myVar2 = m_pShield;
	pSpriteBatch->DrawSprite(m_pSbar, minX + 192.0f, minY + 60.0f, myVar2 + 1.0f, 10.0f, 0, 0);


	//draw score
	int tempvar = GetScore();
	std::string s = std::to_string(tempvar);
	char const *pchar = s.c_str();

	pSpriteBatch->DrawString(m_font, "Score:", minX + 380.0f, minY - 308.0f, 0, 0);
	pSpriteBatch->DrawString(m_font, pchar, minX + 500.0f, minY - 308.0f, 0, 0);
}

void GUI::SetShield(float shield)
{
	m_pShield = shield;
}

void GUI::SetHealth(float health)
{
	m_pHealth = (int)health;
}
void GUI::AddScore(int amount)
{
	m_pScore += amount;
}

int GUI::GetScore()
{
	return m_pScore;
}