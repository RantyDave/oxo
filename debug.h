#ifndef _DEBUG_H
#define _DEBUG_H
#include "mbed.h"

//define NEED_CONSOLE_OUTPUT to get logging via COM3 (on windows) on the PCA10001
#ifdef NEED_CONSOLE_OUTPUT
extern Serial pc;
#define DEBUG(...) { pc.printf(__VA_ARGS__); }
#else
	#define DEBUG(...) /* nothing */
#endif /* #if NEED_CONSOLE_OUTPUT */

#endif
