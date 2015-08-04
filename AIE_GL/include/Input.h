// Author: Aaron Cox
// Description: Basic Keyboard and Mouse Management

// the following functions are provided:
/*-----------------------------------------------------------------------------

	IsKeyDown		( key );	returns true or false
	IsKeyUp			( key );	returns true or false
	WasKeyPressed	( key );	returns true or false
	WasKeyReleased	( key );	returns true or false

	GetPressedKeys( );			// returns a list of pressed physical keys as a const std::vector<unsigned int>

	GetPressedCharacters( );	// returns a list of unicode printable characters (modifier keys are supported)
								// eg if the GLFW_KEY_A button on the keyboard was pressed whilst capslock or shift was on,
								// the list would contain the 'A' character otherwise 'a' character or if shift + '7' was pressed
								// than the list would contain the '&' character

	IsMouseButtonDown( mouseButton );	returns true or false		
	IsMouseButtonUp( mouseButton );		returns true or false

	WasMouseButtonPressed( mouseButton );	returns true or false
	WasMouseButtonReleased( mouseButton );	returns true or false


	// key:			refers to a unique key identifier    eg: GLFW_KEY_SPACE or GLFW_KEY_ESCAPE etc
	// mouseButton:	refers to a unique button identifier eg: GLFW_MOUSE_BUTTON_LEFT or GLFW_MOUSE_BUTTON_RIGHT

-----------------------------------------------------------------------------*/

#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <map>

class Input
{
public:

	static Input *GetSingleton()			{ return ms_singleton; }

	bool IsKeyDown(int keyID);
	bool IsKeyUp(int keyID);
	bool WasKeyPressed(int keyID);
	bool WasKeyReleased(int keyID);

	const std::vector<unsigned int> &GetPressedKeys( );
	const std::vector<unsigned int> &GetPressedCharacters( );

	bool IsMouseButtonDown( int mbID );
	bool IsMouseButtonUp( int mbID );
	bool WasMouseButtonPressed( int mbID );
	bool WasMouseButtonReleased( int mbID );

	int GetMouseX();
	int GetMouseY() ;
	void GetMouseXY(int *x, int *y);

	enum EKeyStatus
	{
		E_JUST_RELEASED,
		E_UP,
		E_JUST_PRESSED,
		E_DOWN,		
	};

	// just giving the Application class access to the Input singleton!
	friend class Application;

protected:

	// singleton stuff
	static Input * ms_singleton;

	// only want the "Application" class to be able to create / destroy
	static void CreateSingleton()			{ ms_singleton = new Input();	}
	static void DestroySingleton()			{ delete ms_singleton;			}

	// should be called once by the application each frame
	// just before glfwPollEvents
	void Update();

private:

	// constructor private for singleton
	Input();
	~Input();


	std::vector<int>			m_keysToUpdate;
	std::map<int, int>			m_keyStatus;

	std::vector<unsigned int>	m_pressedKeys;
	std::vector<unsigned int>	m_pressedCharacters;

	std::vector<int>			m_mouseToUpdate;
	std::map<int, int>			m_mouseState;

	int m_mouseX;
	int m_mouseY;

private:


	// These methods are called by glfw function pointers
	// GLFWkeyFun and GLFWcharFun - see constructor for setup
	// The function pointers are called during the GLFWPollEvents function
	// which is called at the end of the game loop after SwapBuffers
	// effectivelly at the beginning of each frame.
	//-------------------------------------------------------------
	void OnKeyPressed( int keyID );
	void OnKeyReleased( int keyID );
	void OnKeyRepeate(int key);

	void OnCharInput(unsigned int character);
	//-------------------------------------------------------------

	void OnMouseMove(int newXPos, int newYPos);

	void OnMousePressed(int mbID);
	void OnMouseReleased(int mbID);
	
};

#endif