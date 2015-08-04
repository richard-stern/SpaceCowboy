#ifndef GAME_H
#define GAME_H

#include "Application.h"
class SpriteBatch;
class StateMachine;

class Game : public Application
{
public:
	// assets loaded in constructor
	Game(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title);
	void Initialise();
	// assets destroyed in destructor
	virtual ~Game();

	// update / draw called each frame automaticly
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	StateMachine* m_pStateMachine;
};

#endif