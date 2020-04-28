#ifndef GUI_WRAPPER_H
#define GUI_WRAPPER_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
	extern "C" {
#endif

void initScreen();
void shutdownScreen();
void drawScreen();
void writeText(uint32_t row, uint32_t column, const char* str);

#ifdef __cplusplus
	}
#endif

#endif // ifndef GUI_WRAPPER_H
