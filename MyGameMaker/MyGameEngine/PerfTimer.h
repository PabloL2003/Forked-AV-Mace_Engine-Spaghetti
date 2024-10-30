#ifndef __PERFTIMER_H__
#define __PERFTIMER_H__

#include "types.h"

class PerfTimer
{
public:

	// Constructor
	PerfTimer();

	void Start();
	double ReadMs() const;
	uint64 ReadTicks() const;
	void Delay(uint32 ms) const;

private:
	uint64 startTime;
	static uint64 frequency;
};

#endif //__PERFTIMER_H__