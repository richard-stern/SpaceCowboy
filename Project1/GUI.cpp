#include "GUI.h"
#include "SpriteBatch.h"
#include "Player.h"
#include "TextureManager.h"
#include "SpriteBatch.h"
#include "Engine.h";
#include "Game.h"
#include "Font.h"
#include <string>

GUI* GUI::m_pSingleton = nullptr;

GUI::GUI()
{
	//construct the GUI parts

	//health image
	m_pHpImage = TextureManager::GetSingleton()->LoadTexture("hp bar neo.png");

	//health bar
	m_pbar = TextureManager::GetSingleton()->LoadTexture("hp bar green.png");

	//shield image 
	m_pShieldImage = TextureManager::GetSingleton()->LoadTexture("shield final.png");

	//shield bar
	m_pSbar = TextureManager::GetSingleton()->LoadTexture("shield bar.png");

	//font
	m_font = new Font("ocr_a_36px.fnt");
}

GUI::~GUI()
{
}

void GUI::Draw(SpriteBatch* pSpriteBatch, float health)
{
	Engine::GetSingleton()->GetSpriteBatch()->GetViewRect(&minX, &minY, &maxX, &maxY);
	
	//draw the health UI
	pSpriteBatch->DrawSprite(m_pHpImage, minX + 170.0f, minY + 28.0f, 293.0f, 14.0f);

	//Live hp updaterino + logic
	SetHealth(health);
	float myVar = (float)m_pHealth;
	pSpriteBatch->DrawSprite(m_pbar, minX + 88.0f, minY + 27.0f, 226.0f, 10.0f, 0, 0); //change 4th value to change bar length

	//draw the shield UI
	pSpriteBatch->DrawSprite(m_pShieldImage, minX + 169.0f, minY + 58.0f, 293.0f, 14.0f);

	//draw the Shield bar
	pSpriteBatch->DrawSprite(m_pSbar, minX + 88.0f, minY + 58.0f, 1.0f, 10.0f, 0, 0);


	//draw score
	int tempvar = GetScore();
	std::string s = std::to_string(tempvar);
	char const *pchar = s.c_str();

	pSpriteBatch->DrawString(m_font, "Score:", 955.f, 15.f, 0, 0);
	pSpriteBatch->DrawString(m_font, pchar, 1075.f, 15.f, 0, 0);
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