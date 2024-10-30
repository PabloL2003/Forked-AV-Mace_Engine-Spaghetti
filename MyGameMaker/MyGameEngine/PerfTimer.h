#ifndef __PERFTIMER_H__
#define __PERFTIMER_H__

#include "types.h"

class PerfTimer
{
public:

    PerfTimer(int maxFPS = 240); // Constructor con límite de FPS opcional

    void StartFrame();           // Inicia el temporizador para el nuevo cuadro
    void CapFPS();               // Limita el FPS según maxFPS
    double GetDeltaTime() const; // Devuelve el deltaTime en segundos
    double GetFPS() const;       // Devuelve los FPS calculados

private:
    uint64 startTime;            // Tiempo de inicio del cuadro
    uint64 frequency;            // Frecuencia de rendimiento de SDL
    double deltaTime;            // Tiempo transcurrido entre cuadros en segundos
    double fps;                  // FPS actuales calculados
    int maxFPS;                  // Límite de FPS
    double frameDelay;           // Tiempo mínimo por cuadro en milisegundos

	double ReadMs() const;       
};

#endif //__PERFTIMER_H__