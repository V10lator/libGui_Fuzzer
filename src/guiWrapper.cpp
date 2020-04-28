#include <glm/vec4.hpp>

#include <gx2/enum.h>

#include <gui/FreeTypeGX.h>
#include <gui/GuiFrame.h>
#include <gui/GuiImage.h>
#include <gui/GuiText.h>
#include <gui/gx2_ext.h>
#include <gui/memory.h>
#include <gui/video/CVideo.h>

#include <stdbool.h>
#include <stdint.h>

#include "font.h"
#include "guiWrapper.h"

CVideo *renderer;
GuiFrame *tvWindow;
GuiFrame *drcWindow;
FreeTypeGX *font;
uint32_t tvWidth, tvHeight, drcWidth, drcHeight;

#define MAX_TEXTS 8
GuiText *onScreen[MAX_TEXTS];
size_t onScreenIndex = 0;

void initScreen()
{
	libgui_memoryInitialize();
	
	renderer = new CVideo(GX2_TV_SCAN_MODE_720P, GX2_DRC_RENDER_MODE_SINGLE);
	
	tvWidth = renderer->getTvWidth();
	tvHeight = renderer->getTvHeight();
	drcWidth = renderer->getDrcWidth();
	drcHeight = renderer->getDrcHeight();
	
	tvWindow = new GuiFrame(tvWidth, tvHeight);
	tvWindow->setAlignment(ALIGN_TOP_LEFT);
	drcWindow = new GuiFrame(drcWidth, drcHeight);
	drcWindow->setAlignment(ALIGN_TOP_LEFT);
	
	font = new FreeTypeGX(getTTF(), getTTFsize(), true);
	
	GuiText::setPresets(24, glm::vec4(1.0f), tvWidth, ALIGN_TOP_LEFT);
	GuiText::setPresetFont(font);
	
	renderer->tvEnable(true);
	renderer->drcEnable(true);
}

void shutdownScreen()
{
	renderer->tvEnable(false);
	renderer->drcEnable(false);
	
	delete renderer;
	delete tvWindow;
	delete drcWindow;
	delete font;
	
	libgui_memoryRelease();
}

void drawScreen()
{
	renderer->prepareTvRendering();
	tvWindow->draw(renderer);
	renderer->tvDrawDone();
	
	renderer->prepareDrcRendering();
	drcWindow->draw(renderer);
	renderer->drcDrawDone();
	
	tvWindow->removeAll();
	drcWindow->removeAll();
	while(onScreenIndex != 0)
		delete onScreen[--onScreenIndex];
	
	renderer->waitForVSync();
}

void writeText(uint32_t row, uint32_t column, const char *str)
{
	if(onScreenIndex == MAX_TEXTS)
		return;
	
	GuiText *text = new GuiText(str);
	
	text->setAlignment(ALIGN_TOP_LEFT);
	text->setPosition(row * 24, column * 24);
	text->setMaxWidth(tvWidth - row - 200, GuiText::SCROLL_HORIZONTAL);
	
	onScreen[onScreenIndex++] = text;
	tvWindow->append(text);
	drcWindow->append(text);
}
