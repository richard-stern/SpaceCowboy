#include "Game.h"
#include "Engine.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glfw3.h"

#include "TextureManager.h"
#include "CollisionManager.h"
#include "StateMachine.h"

Game::Game(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
}

void Game::Initialise()
{
	TextureManager::CreateSingleton();
	CollisionManager::CreateSingleton();
	m_pStateMachine = new StateMachine();
}

Game::~Game()
{
	delete m_pStateMachine;
	
	CollisionManager::DestroySingleton();
	TextureManager::DestroySingleton();
}

void Game::Update(float deltaTime)
{
	m_pStateMachine->Update(deltaTime);
}

void Game::Draw()
{
	// clear the back buffer
	ClearScreen();
	
	SpriteBatch* pSpritebatch = Engine::GetSingleton()->GetSpriteBatch();
	pSpritebatch->Begin();

	m_pStateMachine->Draw(pSpritebatch);

	pSpritebatch->End();
}