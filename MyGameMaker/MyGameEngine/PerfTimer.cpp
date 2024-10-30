// ----------------------------------------------------
// Slow timer with microsecond precision
// ----------------------------------------------------

#include "PerfTimer.h"
#include <SDL2/SDL_timer.h>

// L1: DONE 2: Fill Constructor, Start(),ReadMs() and ReadTicks() methods
// they are simple, one line each!

PerfTimer::PerfTimer(int maxFPS) : maxFPS(maxFPS), deltaTime(0.0), fps(0.0)
{
	frequency = SDL_GetPerformanceFrequency();
	frameDelay = 1000.0 / maxFPS;
	StartFrame();
}


void PerfTimer::StartFrame()
{
	startTime = SDL_GetPerformanceCounter();
}

double PerfTimer::ReadMs() const
{
    return static_cast<double>(SDL_GetPerformanceCounter() - startTime) * 1000 / frequency;
}

void PerfTimer::CapFPS()
{
    double frameTime = ReadMs(); // Tiempo que duró el cuadro actual en ms
    if (frameTime < frameDelay)
    {
        SDL_Delay(static_cast<Uint32>(frameDelay - frameTime));
    }

    // Calcular deltaTime en segundos después de capar FPS
    deltaTime = ReadMs() / 1000.0;
    fps = deltaTime > 0 ? 1.0 / deltaTime : 0.0; // Evitar división por cero
}

double PerfTimer::GetDeltaTime() const
{
    return deltaTime;
}

double PerfTimer::GetFPS() const
{
    return fps;
}
