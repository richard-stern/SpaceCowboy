#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	// Creating the sprite batch
	m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);
		
	// Load in the textures that we want to use
	m_backgroundTexture = new Texture("./Images/background.png");
		
	// Create the font for use with draw string
	m_font = new Font("./Fonts/calibri_36px.fnt");
		
	// Defaults for mouse X and Y
	m_mouseX = 0;
	m_mouseY = 0;
}

Game1::~Game1()
{
	// DELETE EVERYTHING!!!
	SpriteBatch::Factory::Destroy(m_spritebatch);

	delete m_backgroundTexture;

	delete m_font;
}

void Game1::Update(float deltaTime)
{
	// Get the mouse X and Y position
	Input::GetSingleton()->GetMouseXY(&m_mouseX, &m_mouseY);
}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();
	
	m_spritebatch->Begin();

	// Draw the background
	m_spritebatch->DrawSprite(m_backgroundTexture, 616.0f, 439.0f, (float)m_backgroundTexture->GetWidth() * 2.0f, (float)m_backgroundTexture->GetHeight() * 2.0f);
	
	m_spritebatch->End();
}