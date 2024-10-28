#ifndef __TIMER_H__
#define __TIMER_H__

#include "MyGameEngine/types.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	uint32 ReadSec() const;
	float ReadMSec() const;

private:
	uint32 startTime;
};

#endif //__TIMER_H__
