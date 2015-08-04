/*-----------------------------------------------------------------------------
Author:			Aaron Cox
Description:	Abstract Application Class, Initialises Window, OpenGL and
				Manages the main game loop.

Usage:
Create a "Game" class that inherits from "Application"
-----------------------------------------------------------------------------*/

#ifndef APPLICATION_H
#define APPLICATION_H

class Input;
class Font;
class RenderTexture;
class Texture;
class SpriteBatch;
struct GLFWwindow;

class Application
{
public:

	// constructor
	// creates GLFW window, Setsup OpenGL
	Application(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title);
	
	// unloads openGL, closes GLFW window
	virtual ~Application();

	// returns only when the game loop exits.
	// should only ever be called once
	void RunGame();

	void ToggleVSync();
	void SetVSync(bool enabled);

	// sets m_gameOver = true. This will close the application safelly
	void Quit();

	Input *GetInput();

	GLFWwindow *GetWindowPtr();

	// returns the Frames per seconds
	unsigned int GetFPS() const;

	// returns the width/height of the game window
	unsigned int GetWindowWidth()	const;
	unsigned int GetWindowHeight()	const;

	// returns the with/height of the render target
	// if no alternative render target is specified, the width/height 
	// of the backbuffer is returned (aks the window size)
	unsigned int GetViewWidth() const;
	unsigned int GetViewHeight() const;

	void SetRenderTarget( RenderTexture *renderTarget );
	RenderTexture *GetRenderTarget();

	// clears the screen for a fresh new render
	void ClearScreen();

	// abstract functions
	// must be implemented by derrived classes.
	// Update and Draw are both called once per frame in that order.
	virtual void Update(float deltaTime)	= 0;
	virtual void Draw()						= 0;

private:

	// if set to false, the main game loop will exit
	bool m_gameOver;

	bool m_vSyncEnabled;
	
	// represents the window size
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	// delta time variables
	float m_lastTime, m_currentTime, m_deltaTime;

	// fps calculation
	unsigned int m_fps, m_fpsCount;
	float m_fpsIntervial;

	// ptr to the GLFW window handle.
	GLFWwindow *m_pWindow;

	// helper function to update the FPS
	void UpdateFPS(float dt);

	RenderTexture *m_currentRenderTarget;
};

#endif