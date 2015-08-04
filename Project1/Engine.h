#pragma once

class Application;
class Input;
class SpriteBatch;

class Engine
{
public:
	static void CreateEngine(unsigned int width, unsigned int height, bool fullscreen, char* windowName);
	static void DestroyEngine();
	static Engine *GetSingleton() { return m_pSingleton; }

	//Get pointers to the various systems
	Application* GetApplication();
	Input* GetInput();
	SpriteBatch* GetSpriteBatch();

private:
	Engine();
	~Engine();
	static Engine * m_pSingleton;

	Application* m_pApplication;
	Input* m_pInput;
	SpriteBatch* m_pSpriteBatch;
};


