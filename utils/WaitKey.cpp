#include "WaitKey.h"

#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#include <conio.h>
#include <windows.h>
#else
#endif

#include <future>

int WaitKey(int delay) {}