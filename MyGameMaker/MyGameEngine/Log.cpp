#include "Log.h"

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <tchar.h>

#include "Engine.h"

void Log(const char file[], int line, LogType type, const char* format, ...)
{
	static char tmpString1[BUFFER_SIZE];
	static char tmpString2[BUFFER_SIZE];
	static va_list ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmpString1, BUFFER_SIZE, format, ap);
	va_end(ap);

	sprintf_s(tmpString2, BUFFER_SIZE, "\n%s(%d) : %s", file, line, tmpString1);
	OutputDebugStringA(tmpString2);

	// Log to Editor Console
	sprintf_s(tmpString2, BUFFER_SIZE, "%s", tmpString1);
	Engine::Instance().AddLog(type, tmpString2);
	
}
