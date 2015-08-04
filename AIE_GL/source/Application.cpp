#include "Application.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "glfw3.h"

#include "SpriteBatch.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Font.h"
#include "Input.h"

Application::Application(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title)
{
	// Initialise member variables 
	//----------------------------------------------------------------------------
		m_windowWidth	= windowWidth;
		m_windowHeight	= windowHeight;
		m_gameOver		= false;

		m_currentTime	= (float)glfwGetTime();
		m_lastTime		= m_currentTime;
		m_deltaTime		= 0.0f;

		m_fps			= 0;
		m_fpsCount		= 0;
		m_fpsIntervial	= 0.0f;

		m_currentRenderTarget = nullptr;
	//----------------------------------------------------------------------------
	
	// Setup GLFW
	//----------------------------------------------------------------------------
	glfwInit();

	m_pWindow = glfwCreateWindow(windowWidth, windowHeight, title, (fullscreen ? glfwGetPrimaryMonitor() : NULL) , NULL);

	glfwMakeContextCurrent(m_pWindow);

	// Initialise openGL 
	//----------------------------------------------------------------------------
	
		// STEP 2: Initialise glew (gl extension wrangler)
		glewInit();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH);



	//----------------------------------------------------------------------------

	Input::CreateSingleton();

	SetVSync(true);
}
Application::~Application()
{
	Input::DestroySingleton();
	glfwTerminate();
}

void Application::RunGame()
{
	while( !m_gameOver )
	{
		// calculate deltaTime
		m_lastTime		= m_currentTime;
		m_currentTime	= (float)glfwGetTime();
		m_deltaTime		= m_currentTime - m_lastTime;

		// calculate fps
		UpdateFPS(m_deltaTime);

		Update(m_deltaTime);
		Draw();

		// swaps the front and back buffers
		glfwSwapBuffers( m_pWindow );

		// update input after the game has updated, but before the window events are handled for the next frame
		Input::GetSingleton()->Update();
		
		// handles window events, and calls aproprate callback
		// that have been provided to glfw, eg keyboard or mouse callback functions
		glfwPollEvents();

		// quit if the window's close button has been pressed.
		m_gameOver = m_gameOver || glfwWindowShouldClose(m_pWindow);
	}
}

void Application::UpdateFPS(float dt)
{
	m_fpsIntervial += m_deltaTime;
	m_fpsCount++;

	if( m_fpsIntervial > 0.5f ) // update the fps every half second
	{
		m_fps			= m_fpsCount * 2; // multiply by 2 because we are updateing every half second
		m_fpsCount		= 0;
		m_fpsIntervial	= 0;
	}
}

void Application::Quit()
{
	m_gameOver = true;
}

unsigned int Application::GetWindowWidth() const
{
	return m_windowWidth;
}

unsigned int Application::GetWindowHeight() const
{
	return m_windowHeight;
}

unsigned int Application::GetViewWidth() const
{
	return (m_currentRenderTarget)?m_currentRenderTarget->GetWidth() : m_windowWidth;
}
unsigned int Application::GetViewHeight() const
{
	return (m_currentRenderTarget)?m_currentRenderTarget->GetHeight() : m_windowHeight;
}

GLFWwindow *Application::GetWindowPtr()
{
	return m_pWindow;
}

Input *Application::GetInput()
{
	return Input::GetSingleton();
}

unsigned int Application::GetFPS() const
{
	return m_fps;
}

void Application::SetVSync(bool enabled)
{
	// WARNING - THIS IS WINDOWS ONLY VSYNC CODE!
	// WILL NOT WORK ON OTHER PLATFORMS
	typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    if(wglSwapIntervalEXT)
	{
        wglSwapIntervalEXT( enabled ? 1 : 0 );
		m_vSyncEnabled = enabled;
	}
}

void Application::ToggleVSync()
{
	SetVSync(!m_vSyncEnabled);
}

void Application::SetRenderTarget( RenderTexture *renderTarget )
{
	m_currentRenderTarget = renderTarget;
	if( m_currentRenderTarget != nullptr )
	{
		glBindFramebuffer( GL_FRAMEBUFFER, m_currentRenderTarget->GetFrameBufferHandle() );
	}
	else
	{
		glBindFramebuffer( GL_FRAMEBUFFER, 0);
	}
}
RenderTexture *Application::GetRenderTarget()
{
	return m_currentRenderTarget;
}

void Application::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}