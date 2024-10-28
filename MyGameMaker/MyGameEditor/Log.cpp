#include "Log.h"

#include <windows.h>
#include <stdio.h>

void Log(const char file[], int line, const char* format, ...)
{
    static char tmpString1[4096];
    static char tmpString2[4096];
    static va_list ap;

    // Construct the string from variable arguments
    va_start(ap, line);
    vsprintf_s(tmpString1, sizeof(tmpString1), format, ap);
    va_end(ap);

    sprintf_s(tmpString2, sizeof(tmpString2), "\n%s(%d) : %s", file, line, tmpString1);

    // Asegúrate de que sea OutputDebugStringA
    OutputDebugStringA(tmpString2);
}
