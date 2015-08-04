#include "Engine.h"
#include "Game.h"
#include "Input.h"
#include "SpriteBatch.h"

Engine * Engine::m_pSingleton = nullptr;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::CreateEngine(unsigned int width, unsigned int height, bool fullscreen, char* windowName)
{ 
	m_pSingleton = new Engine(); 
	Game* pGame = new Game(width, height, false, "Game");

	m_pSingleton->m_pApplication = pGame;
	pGame->Initialise();

	m_pSingleton->m_pApplication->SetVSync(false);

	m_pSingleton->m_pInput = Input::GetSingleton();
	m_pSingleton->m_pSpriteBatch = SpriteBatch::Factory::Create(m_pSingleton->m_pApplication, SpriteBatch::GL3);
}

void Engine::DestroyEngine()
{
	SpriteBatch::Factory::Destroy(m_pSingleton->m_pSpriteBatch);
	delete m_pSingleton->m_pApplication;
	delete m_pSingleton; 
}

Application* Engine::GetApplication()
{
	return m_pApplication;
}

Input* Engine::GetInput()
{
	return m_pInput;
}

SpriteBatch* Engine::GetSpriteBatch()
{
	return m_pSpriteBatch;
}