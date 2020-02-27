#include "Timer.h"
#include "SDL\include\SDL_timer.h"
#include "p2Defs.h"

// ---------------------------------------------
Timer::Timer()
{
	Start();
}

// ---------------------------------------------
void Timer::Start()
{
	running = true;
	started_at = SDL_GetTicks();
}

// ---------------------------------------------
void Timer::Stop()
{
	running = false;
	stopped_at = SDL_GetTicks();
}

void Timer::Resume()
{
	running = true;
	started_at = stopped_at;
}

// ---------------------------------------------
uint Timer::Read() const
{
	if (running == true)
	{
		return SDL_GetTicks() - started_at;
	}
	else
	{
		return stopped_at - started_at;
	}
}

float Timer::ReadSec() const
{
	return float(SDL_GetTicks() - started_at) / 1000.0f;
}
